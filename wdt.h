#ifndef WDT_H_
#define WDT_H_
#include <stdint.h>

#define RETRY_TIMES	10

#define UNUSED(x) ((void)(x))  

#define OK  0
#define FAIL -1

typedef uint8_t u8;
typedef uint16_t u16;

enum{
	I2C_WDT_RELOAD_ADD = 0,
	I2C_WDT_INTERVAL_SET_ADD,
	I2C_WDT_INTERVAL_GET_ADD = 3,
	I2C_WDT_INIT_INTERVAL_SET_ADD = 5,
	I2C_WDT_INIT_INTERVAL_GET_ADD = 7,
	I2C_WDT_RESET_COUNT_ADD = 9,
  I2C_WDT_CLEAR_RESET_COUNT_ADD = 11,
};


extern int readReg16(int dev, int add);
extern int readReg24(int dev, int add);
extern int writeReg16(int dev, int add, int val);
extern int writeReg24(int dev, int add, int val);
extern void printbits(int v);
extern int writeReg8(int dev, int add, int val);
extern int readReg8(int dev, int add);
extern int doBoardInit(int hwAdd);

#endif //WDT_H_