#ifndef WDT_H_
#define WDT_H_
#include <stdint.h>

#define RETRY_TIMES	10
#define RTC_SET_CMD 0xaa

#define UNUSED(x) ((void)(x))  

#define OK  0
#define FAIL -1
#define NO_PRINT -2

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

#define WDT_MIN_POWER_OFF_INTERVAL	(int)2
#define WDT_MAX_POWER_OFF_INTERVAL	(int)(31*24*3600)//one month
enum
{
	I2C_WDT_RELOAD_ADD = 0,
	I2C_WDT_INTERVAL_SET_ADD,
	I2C_WDT_INTERVAL_GET_ADD = 3,
	I2C_WDT_INIT_INTERVAL_SET_ADD = 5,
	I2C_WDT_INIT_INTERVAL_GET_ADD = 7,
	I2C_WDT_RESET_COUNT_ADD = 9,
	I2C_WDT_CLEAR_RESET_COUNT_ADD = 11,
	I2C_5V_IN_ADD,
	I2C_POWER_OFF_INTERVAL_SET_ADD = 14,
	I2C_POWER_OFF_INTERVAL_GET_ADD = 18,
	I2C_VBAT_ADD = 22,
	I2C_5V_OUT_ADD = 24,
	I2C_TEMP_ADD = 26,
	I2C_CHARGE_STAT_ADD = 27,
	I2C_POWER_OFF_ON_BATTERY_ADD,
	I2C_POWER_SW_USAGE_ADD,
	I2C_POWER_SW_STATUS_ADD,
	I2C_RTC_YEAR_ADD,
	I2C_RTC_MONTH_ADD,
	I2C_RTC_DAY_ADD,
	I2C_RTC_HOUR_ADD,
	I2C_RTC_MINUTE_ADD,
	I2C_RTC_SECOND_ADD,
	I2C_RTC_SET_YEAR_ADD,
	I2C_RTC_SET_MONTH_ADD,
	I2C_RTC_SET_DAY_ADD,
	I2C_RTC_SET_HOUR_ADD,
	I2C_RTC_SET_MINUTE_ADD,
	I2C_RTC_SET_SECOND_ADD,
	I2C_RTC_CMD_ADD,
	I2C_MEM_REVISION_HW_MAJOR_ADD,
	I2C_MEM_REVISION_HW_MINOR_ADD,
	I2C_MEM_REVISION_MAJOR_ADD,
	I2C_MEM_REVISION_MINOR_ADD,
	SLAVE_BUFF_SIZE
};

enum{
	BOARD_TYPE_WDT = 0,
	BOARD_TYPE_SUPER_WDT,
};
extern int readReg16(int dev, int add);
extern int readReg24(int dev, int add);
extern int writeReg16(int dev, int add, int val);
extern int writeReg24(int dev, int add, int val);
extern void printbits(int v);
extern int writeReg8(int dev, int add, int val);
extern int readReg8(int dev, int add);
int writeReg32(int dev, int add, int val);
int readReg32(int dev, int add);
extern int doBoardInit(int hwAdd, u8* bType);
int readBuff(int dev, int add, uint8_t *data, int len);
int writeBuff(int dev, int add, uint8_t *data, int len);
#endif //WDT_H_
