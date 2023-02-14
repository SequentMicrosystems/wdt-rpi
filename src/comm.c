/*
 * comm.c:
 *	Communication routines "platform specific" 
 *	
 *	Copyright (c) 2016-2018 Sequent Microsystem
 *	<http://www.sequentmicrosystem.com>
 ***********************************************************************
 *	Author: Alexandru Burcea
 ***********************************************************************
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "wdt.h"

#define I2C_SLAVE	0x0703
#define I2C_SMBUS	0x0720	/* SMBus-level access */
#define I2C_MAX_BUFFER_SIZE 32

int i2cSetup(int addr)
{
	int file;
	char filename[40];

	sprintf(filename, "/dev/i2c-1");

	if ( (file = open(filename, O_RDWR)) < 0)
	{
		printf("Failed to open the bus.");
		return FAIL;
	}
	if (ioctl(file, I2C_SLAVE, addr) < 0)
	{
		printf("Failed to acquire bus access and/or talk to slave.\n");
		return FAIL;
	}

	return file;
}

int doBoardInit(int hwAdd, u8 *bType)
{
	int dev, bV = -1;

	dev = i2cSetup(hwAdd);
	if (dev == FAIL)
	{
		return dev;
	}
	bV = readReg8(dev, I2C_WDT_RELOAD_ADD);
	if (bV == FAIL)
	{
		return bV;
	}
	*bType = bV;
	return dev;
}

int readReg8(int dev, int add)
{

	int ret;
	char buf[10];

	buf[0] = 0xff & add;

	if (write(dev, buf, 1) != 1)
	{
		printf("Fail to select mem add\n");
		return -1;
	}

	if (read(dev, buf, 1) != 1)
	{
		printf("Fail to read reg\n");
		return -1;
	}
	ret = 0xff & buf[0];
	return ret;
}

int readReg16(int dev, int add)
{
	int ret = 0;
	char buf[10];

	buf[0] = 0xff & add;

	if (write(dev, buf, 1) != 1)
	{
		printf("Fail to select mem add\n");
		return -1;
	}

	if (read(dev, buf, 2) != 2)
	{
		printf("Fail to read reg\n");
		return -1;
	}
	memcpy(&ret, buf, 2);

	return ret;
}

int readReg32(int dev, int add)
{
	uint32_t ret = 0;
	char buf[10];

	buf[0] = 0xff & add;

	if (write(dev, buf, 1) != 1)
	{
		printf("Fail to select mem add\n");
		return -1;
	}

	if (read(dev, buf, 4) != 4)
	{
		printf("Fail to read reg\n");
		return -1;
	}
	memcpy(&ret, buf, 4);

	return ret;
}

int writeReg8(int dev, int add, int val)
{
	char buf[10];

	buf[0] = 0xff & add;
	buf[1] = 0xff & val;

	if (write(dev, buf, 2) < 0)
	{
		printf("Fail to w8\n");
		return -1;
	}
	return OK;

}

int writeReg16(int dev, int add, int val)
{
	char buf[10];

	buf[0] = 0xff & add;
	memcpy(&buf[1], &val, 2);

	if (write(dev, buf, 3) < 0)
	{
		printf("Fail to w16\n");
		return FAIL;
	}
	return OK;
}

int writeReg32(int dev, int add, int val)
{
	char buf[10];

	buf[0] = 0xff & add;
	memcpy(&buf[1], &val, 4);

	if (write(dev, buf, 5) < 0)
	{
		printf("Fail to w16\n");
		return FAIL;
	}
	return OK;
}

int readReg24(int dev, int add)
{
	int ret = 0;
	char buf[10];

	buf[0] = 0xff & add;

	if (write(dev, buf, 1) != 1)
	{
		printf("Fail to select mem add\n");
		return FAIL;
	}

	if (read(dev, buf, 3) != 2)
	{
		printf("Fail to read reg\n");
		return FAIL;
	}
	memcpy(&ret, buf, 3);

#ifdef DEBUG_I	
	printbits(ret);
	printf("\n");
	printf("%#08x\n", ret);
#endif
	return ret;
}

int writeReg24(int dev, int add, int val)
{
	char buf[10];

	buf[0] = 0xff & add;
	memcpy(&buf[1], &val, 3);

	if (write(dev, buf, 4) < 0)
	{
		printf("Fail to w24\n");
		return FAIL;
	}
	return OK;

}

int readBuff(int dev, int add, uint8_t *data, int len)
{
	char buf[2];

	if (NULL == data || len > I2C_MAX_BUFFER_SIZE)
	{
		return FAIL;
	}

	buf[0] = 0xff & add;

	if (write(dev, buf, 1) != 1)
	{
		printf("Fail to select mem add\n");
		return FAIL;
	}

	if (read(dev, data, len) < 1)
	{
		printf("Fail to read reg\n");
		return FAIL;
	}
	return OK;
}


int writeBuff(int dev, int add, uint8_t *data, int len)
{
	char buf[I2C_MAX_BUFFER_SIZE];

	if (NULL == data || len > I2C_MAX_BUFFER_SIZE -1)
	{
		return FAIL;
	}

	buf[0] = 0xff & add;
	memcpy( buf + 1, data, len);

	if (write(dev, buf, len + 1) < 1)
	{
		printf("Fail to select mem add\n");
		return FAIL;
	}
	return OK;
}
