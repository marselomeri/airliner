extern "C" {
    #include "cfe.h"
}
#include "pmc_app.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>


int32 PMC::InitDevice(const char *device)
{
    uint32 i;
    int mem_fd;

    /* Initialize just in case we were reloaded and the ctor wasn't called. */
    SharedMemCmd = 0;

    //signal(SIGBUS,catch_sigbus);
    mem_fd = open(device, O_RDWR | O_SYNC);
    SharedMemCmd = (PMC_SharedMemCmd_t *) mmap(0, 0x1000, PROT_READ | PROT_WRITE,
                        MAP_SHARED, mem_fd, PMC_RCOUT_ZYNQ_PWM_BASE);
    close(mem_fd);

    if (SharedMemCmd == 0) {
        (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init device.  errno = %u.",
                                 errno);
        return -1;
    }

    for (i = 0; i < PMC_MAX_ZYNQ_PWMS; ++i) {
        SharedMemCmd->PeriodHi[i].Period = Freq2tick(PMC_FREQUENCY_PWM);
        SharedMemCmd->PeriodHi[i].Hi     = Freq2tick(PMC_FREQUENCY_PWM) / 2; // i prefer it is zero at the beginning
        //PX4_ERR("initialize pwm pointer failed.%d, %d", sharedMem_cmd->periodhi[i].period, sharedMem_cmd->periodhi[i].hi);
    }

    OS_TaskDelay(100);
    StopMotors();

    return 0;
}

void PMC::SendOutputs(const uint16 *PWM)
{
    uint32 i = 0;

    /* Convert this to duty_cycle in ns */
    for (i = 0; i < PMC_MAX_ZYNQ_PWMS; ++i) {
        SharedMemCmd->PeriodHi[i].Hi = PMC_TICK_PER_US * PWM[i];
    }
}
