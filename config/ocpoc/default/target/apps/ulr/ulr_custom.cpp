#include "ulr_app.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#define ULR_PORT_SPEED  (115200)

typedef struct
{
	int FD;
} ULR_CustomData_t;

ULR_CustomData_t ULR_CustomData;

int32 ULR::InitDevice(void)
{
	int32 iStatus = CFE_SUCCESS;
	termios uart_config;
	int termios_state;


	OS_printf("ULR::InitDevice\n");

	ULR_CustomData.FD = open(ULR_CUSTOM_PORT_PATH, O_RDWR | O_NOCTTY);
	if (ULR_CustomData.FD < 0)
	{
		iStatus = -1;
		goto end_of_function;
	}

	/* fill the struct for the new configuration */
	tcgetattr(ULR_CustomData.FD, &uart_config);

	// Input flags - Turn off input processing
	//
	// convert break to null byte, no CR to NL translation,
	// no NL to CR translation, don't mark parity errors or breaks
	// no input parity check, don't strip high bit off,
	// no XON/XOFF software flow control
	//
	uart_config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL |
				 INLCR | PARMRK | INPCK | ISTRIP | IXON);

	//
	// Output flags - Turn off output processing
	//
	// no CR to NL translation, no NL to CR-NL translation,
	// no NL to CR translation, no column 0 CR suppression,
	// no Ctrl-D suppression, no fill characters, no case mapping,
	// no local output processing
	//
	//// config.c_oflag &= ~(OCRNL | ONLCR | ONLRET |
	//                     ONOCR | ONOEOT| OFILL | OLCUC | OPOST);

	/* no parity, one stop bit */
	uart_config.c_cflag &= ~(CSTOPB | PARENB);

	//
	// No line processing
	//
	// echo off, echo newline off, canonical mode off,
	// extended input processing off, signal chars off
	//
	uart_config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);

	uart_config.c_oflag = 0;

	/* clear ONLCR flag (which appends a CR for every LF) */
	uart_config.c_oflag &= ~ONLCR;

	/* set baud rate */
	if ((termios_state = cfsetispeed(&uart_config, ULR_PORT_SPEED)) < 0)
	{
		iStatus = -2;
		goto end_of_function;
	}

	if ((termios_state = cfsetospeed(&uart_config, ULR_PORT_SPEED)) < 0)
	{
		iStatus = -3;
		goto end_of_function;
	}

	if ((termios_state = tcsetattr(ULR_CustomData.FD, TCSANOW, &uart_config)) < 0)
	{
		iStatus = -3;
		goto end_of_function;
	}

end_of_function:
	return iStatus;
}


int32 ULR::ReadDevice(uint8 *Buffer, uint32 *Size)
{
	int32 iStatus = CFE_SUCCESS;
	int32 bytesRead = 0;

	bytesRead = read(ULR_CustomData.FD, (void*)&Buffer[0], (int)*Size);
	if(bytesRead < 0)
	{
		iStatus = -1;
	}
	else
	{
		*Size = bytesRead;
	}

end_of_function:
	return iStatus;
}


void ULR::CloseDevice(void)
{
	close(ULR_CustomData.FD);

}

