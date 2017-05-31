#include "hs_custom.h"
#include "hs_app.h"
#include <errno.h>
#include <unistd.h>


#define HS_PROC_STAT_PATH "/proc/stat"

/*
** Event IDs
** Custom Event IDs must not conflict with those in hs_events.h
*/

/** \brief <tt> 'Error Creating Child Task for CPU Utilization Monitoring,RC=0x\%08X' </tt>
**  \event <tt> 'Error Creating Child Task for CPU Utilization Monitoring,RC=0x\%08X' </tt>
**
**  \par Type: ERROR
**
**  \par Cause:
**
**  This event message is issued when CFS Health and Safety
**  is unable to create its child task via the #CFE_ES_CreateChildTask
**  API
**
**  The \c RC field contains the return status from the
**  #CFE_ES_CreateChildTask call that generated the error
*/
#define HS_PROC_STAT_OPEN_ERR_EID 101

typedef struct {
	long unsigned int minflt;
	long unsigned int cminflt;
	long unsigned int majflt;
	long unsigned int cmajflt;
	long unsigned int utime;
	long unsigned int stime;
	long unsigned int cutime;
	long unsigned int cstime;
	int               nice;
	long unsigned int nswap;
	long unsigned int cnswap;
	long unsigned int vsize;
	long unsigned int rss;
	long unsigned int cpuTotalTime;
} HS_ProcStat;

typedef struct {
	long unsigned int user;
	long unsigned int nice;
	long unsigned int system;
	long unsigned int idle;
	long unsigned int iowait;
	long unsigned int irq;
	long unsigned int softirq;
	long unsigned int steal;
	long unsigned int guest;
	long unsigned int guest_nice;
	long unsigned int cpuTotalTime;
} HS_CpuStat;

/*
** Custom Global Data Structure
*/
typedef struct
{
	pid_t	SelfPID;
	uint32	UtilCycleCounter;/**< \brief Counter to determine when to monitor utilization */
	HS_ProcStat PrevProcStat;
	HS_CpuStat PrevCpuStat;
	boolean InitComplete;
} HS_CustomData_t;

HS_CustomData_t HS_CustomData;



int32 HS_CustomInit(void)
{
	HS_CustomData.SelfPID = getpid();

	return CFE_SUCCESS;
}



void HS_CustomCleanup(void)
{
}



void HS_CustomMonitorUtilization(void)
{
    HS_CustomData.UtilCycleCounter++;
    if (HS_CustomData.UtilCycleCounter >= HS_UTIL_CYCLES_PER_INTERVAL)
    {
        HS_MonitorUtilization();
        HS_CustomData.UtilCycleCounter = 0;
    }
}



int32 HS_GetUsage(const pid_t pid, HS_ProcStat* proc, HS_CpuStat *cpu)
{
	int32 status = CFE_SUCCESS;
	char sPid[20];
	long int rss;
	char statFilepath[30] = "/proc/";
	FILE *hProcStat;
	FILE *hCpuStat;

	snprintf(sPid, sizeof(sPid), "%d", pid);

	strncat(statFilepath, sPid, sizeof(statFilepath) - strlen(statFilepath) - 1);
	strncat(statFilepath, "/stat", sizeof(statFilepath) - strlen(statFilepath) - 1);

	hProcStat = fopen(statFilepath, "r");
	if(hProcStat == NULL)
	{
	    CFE_EVS_SendEvent(HS_PROC_STAT_OPEN_ERR_EID, CFE_EVS_INFORMATION,
	                      "Failed to open '%s'.  errno=%i.",
						  statFilepath,
						  errno);
	    status = -1;
	    goto end_of_function;
	}

	hCpuStat = fopen(HS_PROC_STAT_PATH, "r");
	if(hCpuStat == NULL)
	{
	    CFE_EVS_SendEvent(HS_PROC_STAT_OPEN_ERR_EID, CFE_EVS_INFORMATION,
	                      "Failed to open '%s'.  errno=%u.",
						  HS_PROC_STAT_PATH,
						  errno);
	    status = -1;
	    goto end_of_function;
	}

	bzero(proc, sizeof(HS_ProcStat));
	if(fscanf(hProcStat, "%*d %*s %*c %*d %*d %*d %*d %*d %*u %lu %lu %lu %lu %lu"
			"%lu %ld %ld %*d %*d %*d %*d %*u %lu %ld",
			&proc->minflt,
			&proc->cminflt,
			&proc->majflt,
			&proc->cmajflt,
			&proc->utime,
			&proc->stime,
			&proc->cutime,
			&proc->cstime,
			&proc->nice,
			&proc->nswap,
			&proc->cnswap,
			&proc->cutime,
			&proc->cstime,
			&proc->vsize,
			&proc->rss) == EOF)
	{
		fclose(hProcStat);
	    status = -1;
	    goto end_of_function;
	}

	fclose(hProcStat);
	proc->rss = rss * getpagesize();

	/* Read and calculate CPU total time from /proc/stat */
	bzero(cpu, sizeof(HS_CpuStat));
	if(fscanf(hCpuStat, "%*s %lu %lu %lu %lu %lu %lu %lu %*lu %*lu %*lu",
		&cpu->user,
		&cpu->nice,
		&cpu->system,
		&cpu->idle,
		&cpu->iowait,
		&cpu->irq,
		&cpu->softirq,
		&cpu->steal,
		&cpu->guest,
		&cpu->guest_nice,
		&cpu->softirq) == EOF)
	{
		fclose(hCpuStat);
	    status = -1;
	    goto end_of_function;
	}

	fclose(hCpuStat);
	cpu->cpuTotalTime =
			cpu->user +
			cpu->nice +
			cpu->system +
			cpu->idle +
			cpu->iowait +
			cpu->irq +
			cpu->softirq +
			cpu->steal +
			cpu->guest +
			cpu->guest_nice;
	proc->cpuTotalTime = cpu->cpuTotalTime;

end_of_function:
	return status;
}



void HS_CalcProcUsagePct(const HS_ProcStat* curUsage, const HS_ProcStat* lastUsage,
						 double *usage)
{
	const long unsigned int cpuDiff = curUsage->cpuTotalTime - lastUsage->cpuTotalTime;
	const long unsigned int pidDiff =
			(curUsage->utime + curUsage->stime) -
			(lastUsage->utime + lastUsage->stime);

	*usage = HS_UTIL_PER_INTERVAL_TOTAL * ((double)pidDiff / (double)cpuDiff);
}



void HS_CalcCpuUsagePct(const HS_CpuStat* curUsage, const HS_CpuStat* lastUsage,
						 double *usage)
{
	const long unsigned int cpuDiff = curUsage->cpuTotalTime - lastUsage->cpuTotalTime;
	const long unsigned int nonIdleDiff =
			(curUsage->user + curUsage->system) -
			(lastUsage->user + lastUsage->system);
	*usage = HS_UTIL_PER_INTERVAL_TOTAL * ((double)nonIdleDiff / (double)cpuDiff);
}



int32 HS_CustomGetUtil(void)
{
	int32 status = CFE_SUCCESS;
	HS_ProcStat curProcStat;
	HS_CpuStat curCpuStat;
	double pctProc = 0.0;
	double pctCpu = 0.0;
	double pct = 0.0;

	if(HS_CustomData.InitComplete == FALSE)
	{
		status = HS_GetUsage(HS_CustomData.SelfPID, &HS_CustomData.PrevProcStat, &HS_CustomData.PrevCpuStat);
		HS_CustomData.InitComplete = TRUE;
	}
	else
	{
		status = HS_GetUsage(HS_CustomData.SelfPID, &curProcStat, &curCpuStat);
		HS_CalcProcUsagePct(&curProcStat, &HS_CustomData.PrevProcStat, &pctProc);
		HS_CalcCpuUsagePct(&curCpuStat, &HS_CustomData.PrevCpuStat, &pctCpu);

		pct = pctCpu;

		memcpy(&HS_CustomData.PrevProcStat, &curProcStat, sizeof(HS_ProcStat));
		memcpy(&HS_CustomData.PrevCpuStat, &curCpuStat, sizeof(HS_CpuStat));
	}

	return pct;
}



int32 HS_CustomCommands(CFE_SB_MsgPtr_t MessagePtr)
{
	/* Do nothing. */
	return 0;
}
