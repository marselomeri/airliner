/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpiops.h"
#include "xspips.h"

void init_gpio(void);
void init_spi(void);
//void init_uart(void);
//void init_i2c(void);
void enable_microblaze(void);
void init_baro(void);
void read_baro(void);
void init_imu(void);
void read_imu(void);

/*
 * The following are declared globally so they are zeroed and can be
 * easily accessible from a debugger.
 */
XGpioPs Gpio;	/* The driver instance for GPIO Device. */
XSpiPs  Spi0;	/* The driver instance for SPI-0 Device. */
XSpiPs  Spi1;	/* The driver instance for SPI-1 Device. */

#define MS5611_SPI_CMD_RESET                (0x1e)
#define MS5611_SPI_CMD_PROM_READ_MASK       (0xa0)
#define MS5611_SPI_CMD_PROM_ADDR_SHIFT      (1)

#define MPU9250_BIT_H_RESET                 (0x80)
#define MPU9250_REG_PWR_MGMT_1              (0x6B)
#define MPU9250_REG_WHOAMI                  (0x75)


int main()
{
    init_platform();
    s32 Status;
    u8 SendBuffer[30];
    u8 RecvBuffer[30];

    sleep(10);

    init_gpio();
    init_spi();
    //init_uart();
    //init_i2c();
    enable_microblaze();
    init_baro();
    init_imu();

    while(1)
    {
        // read_baro();
        read_imu();

    	usleep(4000);
    }

    cleanup_platform();

    return 0;
}


void init_gpio(void)
{
	XGpioPs_Config *ConfigPtr;
	s32 Status;

    xil_printf("A53-0:  Looking up GPIO PS config\n\r");
    ConfigPtr = XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);

    xil_printf("A53-0:  Initializing GPIO PS\n\r");
    Status = XGpioPs_CfgInitialize(&Gpio, ConfigPtr,
    					ConfigPtr->BaseAddr);
    if (Status != XST_SUCCESS)
    {
    	while(1)
    	{
    	    xil_printf("A53-0:  XGpioPs_CfgInitialize failed.\n\r");
    	    sleep(1);
    	}
    }

    xil_printf("A53-0:  Setting GPIO PS pin direction.\n\r");
    XGpioPs_SetDirectionPin(&Gpio, 78, 1);

    xil_printf("A53-0:  Enabling GPIO PS pin.\n\r");
    XGpioPs_SetOutputEnablePin(&Gpio, 78, 1);
}


void init_spi(void)
{
	XSpiPs_Config *ConfigPtr;
	s32 Status;

    xil_printf("A53-0:  Looking up SPI-0 PS config\n\r");
    ConfigPtr = XSpiPs_LookupConfig(XPAR_XSPIPS_0_DEVICE_ID);

    xil_printf("A53-0:  Initializing SPI-0 PS\n\r");
    Status = XSpiPs_CfgInitialize(&Spi0, ConfigPtr,
    					ConfigPtr->BaseAddress);
    if (Status != XST_SUCCESS)
    {
    	while(1)
    	{
    	    xil_printf("A53-0:  XSpiPs_CfgInitialize failed.\n\r");
    	    sleep(1);
    	}
    }

    Status = XSpiPs_SelfTest(&Spi0);
    if (Status != XST_SUCCESS)
    {
    	while(1)
    	{
    	    xil_printf("A53-0:  XSpiPs_SelfTest failed.\n\r");
    	    sleep(1);
    	}
    }

    Status = XSpiPs_SetOptions(&Spi0, XSPIPS_MANUAL_START_OPTION |
    		XSPIPS_MASTER_OPTION | XSPIPS_FORCE_SSELECT_OPTION);
    if (Status != XST_SUCCESS)
    {
    	while(1)
    	{
    	    xil_printf("A53-0:  XSpiPs_SetOptions failed.\n\r");
    	    sleep(1);
    	}
    }

    /* Set clock to 10.42MHz */
    Status = XSpiPs_SetClkPrescaler(&Spi0, XSPIPS_CLK_PRESCALE_16);
    if (Status != XST_SUCCESS)
    {
    	while(1)
    	{
    	    xil_printf("A53-0:  XSpiPs_SetClkPrescaler failed.\n\r");
    	    sleep(1);
    	}
    }

}


//void init_uart(void)
//{
//
//}


//void init_i2c(void)
//{
//
//}


void enable_microblaze(void)
{
    xil_printf("A53-0:  Enabling Microblaze-0.\n\r");
    XGpioPs_WritePin(&Gpio, 78, 1);
    xil_printf("A53-0:  Microblaze-0 enabled.\n\r");

}


void init_baro(void)
{
    u8 SendBuffer[30];
    u8 RecvBuffer[30];
	s32 Status;

    XSpiPs_SetSlaveSelect(&Spi0, 0);

    memset(SendBuffer, 0, sizeof(SendBuffer));
    memset(RecvBuffer, 0, sizeof(RecvBuffer));

    SendBuffer[0] = MS5611_SPI_CMD_RESET;
    Status = XSpiPs_PolledTransfer(&Spi0, SendBuffer, 0, 1);
    if (Status != XST_SUCCESS)
    {
    	while(1)
    	{
    	    xil_printf("A53-0:  XSpiPs_PolledTransfer failed.\n\r");
    	    sleep(1);
    	}
    }
}



void read_baro(void)
{
    u8 SendBuffer[30];
    u8 RecvBuffer[30];
	s32 Status;

    memset(SendBuffer, 0, sizeof(SendBuffer));
    memset(RecvBuffer, 0, sizeof(RecvBuffer));

    SendBuffer[0] = MS5611_SPI_CMD_PROM_READ_MASK + (1 << MS5611_SPI_CMD_PROM_ADDR_SHIFT);

    XSpiPs_SetSlaveSelect(&Spi0, 0);
    Status = XSpiPs_PolledTransfer(&Spi0, SendBuffer, RecvBuffer, 3);
	if (Status != XST_SUCCESS)
	{
		while(1)
		{
			xil_printf("A53-0:  XSpiPs_PolledTransfer failed.\n\r");
			sleep(1);
		}
	}

    xil_printf("A53-0:  SPI-0  %02x%02x\n\r", RecvBuffer[1], RecvBuffer[2]);
}



void init_imu(void)
{
    u8 SendBuffer[30];
    u8 RecvBuffer[30];
	s32 Status;

    XSpiPs_SetSlaveSelect(&Spi1, 0);

    memset(SendBuffer, 0, sizeof(SendBuffer));
    memset(RecvBuffer, 0, sizeof(RecvBuffer));

    SendBuffer[0] = MPU9250_BIT_H_RESET;
    SendBuffer[1] = MPU9250_REG_PWR_MGMT_1;
    Status = XSpiPs_PolledTransfer(&Spi1, SendBuffer, 0, 2);
    if (Status != XST_SUCCESS)
    {
    	while(1)
    	{
    	    xil_printf("A53-0:  XSpiPs_PolledTransfer failed.\n\r");
    	    sleep(1);
    	}
    }
}



void read_imu(void)
{
    u8 SendBuffer[30];
    u8 RecvBuffer[30];
	s32 Status;

    memset(SendBuffer, 0, sizeof(SendBuffer));
    memset(RecvBuffer, 0, sizeof(RecvBuffer));

    SendBuffer[0] = MPU9250_REG_WHOAMI;
    Status = XSpiPs_PolledTransfer(&Spi1, SendBuffer, 0, 2);
    if (Status != XST_SUCCESS)
    {
    	while(1)
    	{
    	    xil_printf("A53-0:  XSpiPs_PolledTransfer failed.\n\r");
    	    sleep(1);
    	}
    }

    xil_printf("A53-0:  SPI-0  %02x\n\r", RecvBuffer[1]);
}
