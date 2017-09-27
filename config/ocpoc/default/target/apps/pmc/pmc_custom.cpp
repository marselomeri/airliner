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

#define PMC_RCOUT_ZYNQ_PWM_BASE (0x43c00000)
#define PMC_FREQUENCY_PWM       (400)
#define PMC_TICK_PER_S          (50000000)
#define PMC_TICK_PER_US         (50)
#define PMC_DEVICE_PATH         "/dev/mem"


typedef struct {
    uint32 Period;
    uint32 Hi;
} PMC_PeriodHi_t;

typedef struct
{
     PMC_PeriodHi_t PeriodHi[PMC_MAX_MOTOR_OUTPUTS];
} PMC_SharedMemCmd_t;

volatile PMC_SharedMemCmd_t *SharedMemCmd;


uint32 PMC_Freq2tick(uint16 FreqHz);


int32 PMC::InitDevice(void)
{
    uint32 i;
    int mem_fd;

    /* Initialize just in case we were reloaded and the ctor wasn't called. */
    SharedMemCmd = 0;

    //signal(SIGBUS,catch_sigbus);
    mem_fd = open(PMC_DEVICE_PATH, O_RDWR | O_SYNC);
    SharedMemCmd = (PMC_SharedMemCmd_t *) mmap(0, 0x1000, PROT_READ | PROT_WRITE,
                        MAP_SHARED, mem_fd, PMC_RCOUT_ZYNQ_PWM_BASE);
    close(mem_fd);

    if (SharedMemCmd == 0) {
        (void) CFE_EVS_SendEvent(PMC_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init device.  errno = %u.",
                                 errno);
        return -1;
    }

    for (i = 0; i < PMC_MAX_MOTOR_OUTPUTS; ++i) {
        SharedMemCmd->PeriodHi[i].Period = PMC_Freq2tick(PMC_FREQUENCY_PWM);
        SharedMemCmd->PeriodHi[i].Hi     = PMC_Freq2tick(PMC_FREQUENCY_PWM) / 2; // i prefer it is zero at the beginning
        //PX4_ERR("initialize pwm pointer failed.%d, %d", sharedMem_cmd->periodhi[i].period, sharedMem_cmd->periodhi[i].hi);
    }

    OS_TaskDelay(100);
    StopMotors();

    return 0;
}

void PMC::SetMotorOutputs(const uint16 *PWM)
{
    uint32 i = 0;

    /* Convert this to duty_cycle in ns */
    for (i = 0; i < PMC_MAX_MOTOR_OUTPUTS; ++i) {
        SharedMemCmd->PeriodHi[i].Hi = PMC_TICK_PER_US * PWM[i];
    }
}



uint32 PMC_Freq2tick(uint16 FreqHz)
{
    uint32 duty = PMC_TICK_PER_S / (unsigned long)FreqHz;
    return duty;
}
