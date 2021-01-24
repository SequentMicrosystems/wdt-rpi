#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wdt.h"

#define WDT_SOFTWARE_VER_STR  "2.00"

#define WDT_HW_ADD 0x30
#define WDT_RELOAD_KEY  0xCA
#define WDT_RESET_COUNT_KEY	0xBE

#define WDT_DEFAULT_PERIOD_MIN  11
#define WDT_DEFAULT_PERIOD_MAX  64999
#define WDT_DISABLE_PERIOD      65001
#define WDT_PERIOD_MAX  0xffff
#define WDT_OFF_INTERVAL_MAX	0x7fffffff

char *usage = "Usage:   wdt -h/-help <command>\n"
	"         wdt -warranty\n"
	"         wdt -r/-reload\n"
	"         wdt -d/-default <value>\n"
	"         wdt -p/-period <value>\n"
	"         wdt -off/-offinterval <value>\n"
	"         wdt -g/-get <option>\n"
	"         wdt -c/-clear\n"
	"         wdt -v/-version\n"
	"         wdt -rob/-repoweronbattery\n"
   "         wdt -pbe/-powerbuttonenable\n"
	"Type wdt -h <command> for more help"; // No trailing newline needed here.

char *warranty =
	"	       Copyright (c) 2016-2019 Sequent Microsystems\n"
		"                                                             \n"
		"		This program is free software; you can redistribute it and/or modify\n"
		"		it under the terms of the GNU Leser General Public License as published\n"
		"		by the Free Software Foundation, either version 3 of the License, or\n"
		"		(at your option) any later version.\n"
		"                                    \n"
		"		This program is distributed in the hope that it will be useful,\n"
		"		but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
		"		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
		"		GNU Lesser General Public License for more details.\n"
		"			\n"
		"		You should have received a copy of the GNU Lesser General Public License\n"
		"		along with this program. If not, see <http://www.gnu.org/licenses/>.";

void doHelp(int argc, char *argv[])
{
	if (argc == 3)
	{
		if (strcasecmp(argv[2], "-warranty") == 0)
		{
			printf("\t-warranty:   Display the warranty\n");
			printf("\tUsage:       wdt -warranty\n");
			printf("\tExample:     wdt -warranty\n");
		}
		else if (strcasecmp(argv[2], "-r") == 0
			|| strcasecmp(argv[2], "-reload") == 0)
		{
			printf(
				"\t-r/-reload:  Reload the timer, prevent Raspberry Pi to be repowered\n");
			printf("\tUsage:       wdt -r\n");
			printf("\tExample:     wdt -r\n");
		}
		else if (strcasecmp(argv[2], "-d") == 0
			|| strcasecmp(argv[2], "-default") == 0)
		{
			printf(
				"\t-d/-default: Set the default period (sec); The watchdog will reload this period after reset\n");
			printf("\tUsage:       wdt -d <value>\n");
			printf("\tUsage:       wdt -default <value>\n");
			printf("\tExample:     Set the default period to 270 seconds:\n");
			printf("\t             wdt -d 270\n");
		}
		else if (strcasecmp(argv[2], "-p") == 0
			|| strcasecmp(argv[2], "-period") == 0)
		{
			printf("\t-p/-period:  Set the current period and reload the timer\n");
			printf("\tUsage:       wdt -p <value>\n");
			printf(
				"\tExample:     Set the wdt period to 20 sec and reload the timer:\n");
			printf("\t             wdt -p 20\n");
			printf("\tExample:     Disable the watchdog:\n");
			printf("\t             wdt -p 0\n");
		}
		else if (strcasecmp(argv[2], "-c") == 0
			|| strcasecmp(argv[2], "-clear") == 0)
		{
			printf("\t-c/-clear:   Clear the reset counter  \n");
			printf("\tUsage:       wdt -c\n");
			printf("\tExample:     wdt -c\n");
		}
		else if (strcasecmp(argv[2], "-off") == 0
			|| strcasecmp(argv[2], "-offinterval") == 0)
		{
			printf(
				"\t-off/-offinterval:   Set the off interval (seconds), The Raspberry will keept off this amount of time when the repower operation is performed\n");
			printf("\tUsage:       wdt -off <value>\n");
			printf("\tExample:     Set the wdt off period to 1 hour:\n");
			printf("\t             wdt -off 3600\n");
		}
		else if (strcasecmp(argv[2], "-g") == 0
			|| strcasecmp(argv[2], "-get") == 0)
		{
			printf("\t-g/-get:     Get watchdog parameters\n");
			printf("\tUsage:       wdt -g <option>\n");
			printf("\t<option>:    d/default = default period(sec)\n");
			printf("\t             p/period = period(sec)\n");
			printf(
				"\t             r/resets = total number of resets performed \n");
			printf("\t             v/vin = input voltage(mV)\n");
			printf(
				"\t             off/offinterval = how mutch wdt keep raspberry powered off (sec) \n");
			printf("\t             vr/vrasp = Raspberry voltage(mV)\n");
			printf("\t             vb/vbat = Battery voltage(mV)\n");
			printf(
				"\t             c/charge = charge status (0 - off, 1 - charge complete, 2 - charging, 3 - fault)\n");
			printf(
				"\t             rob/repoweronbattery = if the watchdog power off the Raspberry, will repower on battery only if this is 1\n");
			printf(
				"\t             pbe/powerbuttonenable = power button enabled/disabled (1/0)\n");
			printf(
				"\t             pbs/powerbuttonstatus = 1 - power button has been pushed; 0 - not  \n");
			printf("\tExample:     wdt -g d get the wdt default period \n");
		}
		else if (strcasecmp(argv[2], "-rob") == 0
			|| strcasecmp(argv[2], "-repoweronbattery") == 0)
		{
			printf(
				"\t-rob/-repoweronbattery:   Set the \"repower on battery\" flag, 1-power back on Raspberry if the main power i missing, 0 - wait for main power \n");
			printf("\tUsage:       wdt -rob <value>\n");
			printf(
				"\tExample:     Do not power back on Raspberry if on battery\n");
			printf("\t             wdt -rob 0\n");
		}
		else if (strcasecmp(argv[2], "-pbe") == 0
			|| strcasecmp(argv[2], "-powerbuttonenable") == 0)
		{
			printf(
				"\t-pbe/-powerbuttonenable:   Enable / disable the power button, you can read his status and it can power back on raspberry if is pushed \n");
			printf("\tUsage:       wdt -pbe <value>\n");
			printf("\tExample:     Enable power button\n");
			printf("\t             wdt -pbe 1\n");
		}
		else
		{
			printf("Invalid command!\n");
			printf("%s: %s\n", argv[0], usage);
		}
	}
	else
	{
		printf("%s: %s\n", argv[0], usage);
	}
}

static int doReload(int argc, char* argv[])
{
	int dev = 0;
	u8 bType = 0;
	UNUSED(argv);

	if (argc != 2)
	{
		printf("Invalid number of arguments\n");
		return FAIL;
	}

	dev = doBoardInit(WDT_HW_ADD, &bType);
	if (dev <= 0)
	{
		return FAIL;
	}
	return writeReg8(dev, I2C_WDT_RELOAD_ADD, WDT_RELOAD_KEY);
}

static int doDefault(int argc, char* argv[])
{
	int dev = 0;
	int val = 0;
	u8 bType = 0;

	if (argc != 3)
	{
		printf("Invalid number of arguments\n");
		return FAIL;
	}

	dev = doBoardInit(WDT_HW_ADD, &bType);
	if (dev <= 0)
	{
		return FAIL;
	}
	val = atoi(argv[2]);
	if ( (WDT_DEFAULT_PERIOD_MIN <= val) && (val <= WDT_DEFAULT_PERIOD_MAX))
	{
		return writeReg16(dev, I2C_WDT_INIT_INTERVAL_SET_ADD, val);
	}
	return FAIL;
}

static int doPeriod(int argc, char* argv[])
{
	int dev = 0;
	int val = 0;
	u8 bType = 0;

	if (argc != 3)
	{
		printf("Invalid number of arguments\n");
		return FAIL;
	}

	dev = doBoardInit(WDT_HW_ADD, &bType);
	if (dev <= 0)
	{
		return FAIL;
	}
	val = atoi(argv[2]);
	if ( (0 < val) && (val <= WDT_PERIOD_MAX))
	{
		return writeReg16(dev, I2C_WDT_INTERVAL_SET_ADD, val);
	}
	else if (val == 0)
	{
		return writeReg16(dev, I2C_WDT_INTERVAL_SET_ADD, WDT_DISABLE_PERIOD);
	}
	return FAIL;
}

static int doClear(int argc, char* argv[])
{
	int dev = 0;
	u8 bType = 0;

	UNUSED(argv);

	if (argc != 2)
	{
		printf("Invalid number of arguments\n");
		return FAIL;
	}

	dev = doBoardInit(WDT_HW_ADD, &bType);
	if (dev <= 0)
	{
		return FAIL;
	}

	return writeReg16(dev, I2C_WDT_CLEAR_RESET_COUNT_ADD, WDT_RESET_COUNT_KEY);
}

static int doSetOffTime(int argc, char* argv[])
{
	int dev = 0;
	int val = 0;
	u8 bType = 0;

	if (argc != 3)
	{
		printf("Invalid number of arguments\n");
		return FAIL;
	}

	dev = doBoardInit(WDT_HW_ADD, &bType);
	if (dev <= 0)
	{
		return FAIL;
	}
	val = atoi(argv[2]);
	if ( (WDT_MIN_POWER_OFF_INTERVAL < val)
		&& (val < WDT_MAX_POWER_OFF_INTERVAL))
	{
		return writeReg32(dev, I2C_POWER_OFF_INTERVAL_SET_ADD, val);
	}
	return FAIL;
}

static int doGet(int argc, char* argv[])
{
	int dev = 0;
	int val = 0;
	u8 bType = 0;

	if (argc != 3)
	{
		printf("Invalid number of arguments\n");
		return FAIL;
	}

	dev = doBoardInit(WDT_HW_ADD, &bType);
	if (dev <= 0)
	{
		return FAIL;
	}

	if (strcasecmp(argv[2], "d") == 0 || strcasecmp(argv[2], "default") == 0)
	{
		val = readReg16(dev, I2C_WDT_INIT_INTERVAL_GET_ADD);
	}
	else if (strcasecmp(argv[2], "p") == 0 || strcasecmp(argv[2], "period") == 0)
	{
		val = readReg16(dev, I2C_WDT_INTERVAL_GET_ADD);
	}
	else if (strcasecmp(argv[2], "r") == 0 || strcasecmp(argv[2], "resets") == 0)
	{
		val = readReg16(dev, I2C_WDT_RESET_COUNT_ADD);
	}
	else if (strcasecmp(argv[2], "v") == 0 || strcasecmp(argv[2], "vin") == 0)
	{
		val = readReg16(dev, I2C_5V_IN_ADD);
	}
	else if (strcasecmp(argv[2], "off") == 0
		|| strcasecmp(argv[2], "offinterval") == 0)
	{
		val = readReg32(dev, I2C_POWER_OFF_INTERVAL_GET_ADD);
	}
	else if (strcasecmp(argv[2], "vr") == 0 || strcasecmp(argv[2], "vrasp") == 0)
	{
		if (BOARD_TYPE_WDT == bType)
		{
			printf("Available for super-watchdog only!\n");
			return FAIL;
		}
		val = readReg16(dev, I2C_5V_OUT_ADD);
	}
	else if (strcasecmp(argv[2], "vb") == 0 || strcasecmp(argv[2], "vbat") == 0)
	{
		if (BOARD_TYPE_WDT == bType)
		{
			printf("Available for super-watchdog only!\n");
			return FAIL;
		}
		val = readReg16(dev, I2C_VBAT_ADD);
	}
	else if (strcasecmp(argv[2], "t") == 0 || strcasecmp(argv[2], "temp") == 0)
	{
		if (BOARD_TYPE_WDT == bType)
		{
			printf("Available for super-watchdog only!\n");
			return FAIL;
		}
		val = readReg8(dev, I2C_TEMP_ADD);
	}
	else if (strcasecmp(argv[2], "c") == 0 || strcasecmp(argv[2], "charge") == 0)
	{
		if (BOARD_TYPE_WDT == bType)
		{
			printf("Available for super-watchdog only!\n");
			return FAIL;
		}
		val = 0x0f & readReg8(dev, I2C_CHARGE_STAT_ADD);
	}
	else if (strcasecmp(argv[2], "rob") == 0
		|| strcasecmp(argv[2], "repoweronbattery") == 0)
	{
		if (BOARD_TYPE_WDT == bType)
		{
			printf("Available for super-watchdog only!\n");
			return FAIL;
		}
		val = readReg8(dev, I2C_CHARGE_STAT_ADD);
		if ( (val & 0xf0) == 0)
		{
			printf("Not available on this firmware version!\n");
			return FAIL;
		}
		val = 0x01 & (~readReg8(dev, I2C_POWER_OFF_ON_BATTERY_ADD));
		return val;
	}
	else if (strcasecmp(argv[2], "pbe") == 0
		|| strcasecmp(argv[2], "powerbuttonenable") == 0)
	{
		if (BOARD_TYPE_WDT == bType)
		{
			printf("Available for super-watchdog only!\n");
			return FAIL;
		}
		val = readReg8(dev, I2C_CHARGE_STAT_ADD);
		if ( (val & 0xf0) <= 0x10)
		{
			printf("Not available on this firmware version!\n");
			return FAIL;
		}
		val = 0x01 & (readReg8(dev, I2C_POWER_SW_USAGE_ADD));
		return val;
	}
	else if (strcasecmp(argv[2], "pbs") == 0
		|| strcasecmp(argv[2], "powerbuttonstatus") == 0)
	{
		if (BOARD_TYPE_WDT == bType)
		{
			printf("Available for super-watchdog only!\n");
			return FAIL;
		}
		val = readReg8(dev, I2C_CHARGE_STAT_ADD);
		if ( (val & 0xf0) <= 0x10)
		{
			printf("Not available on this firmware version!\n");
			return FAIL;
		}
		val = 0x01 & (readReg8(dev, I2C_POWER_SW_STATUS_ADD));
		return val;
	}
	else
	{
		printf("Invalid  option for -get command\n");
		return FAIL;
	}
	return val;
}

static int doSetRepowerOnBattery(int argc, char *argv[])
{
	int dev = 0;
	int val = 0;
	u8 bType = 0;
	u8 out = 0;

	if (argc != 3)
	{
		printf("Invalid number of arguments\n");
		return FAIL;
	}

	dev = doBoardInit(WDT_HW_ADD, &bType);
	if (dev <= 0)
	{
		return FAIL;
	}
	val = readReg8(dev, I2C_CHARGE_STAT_ADD);
	if ( (val & 0xf0) == 0)
	{
		printf("Not available on this firmware version!\n");
		return FAIL;
	}
	val = atoi(argv[2]);

	if (val == 0)
	{
		out = 1;
	}

	return writeReg8(dev, I2C_POWER_OFF_ON_BATTERY_ADD, out);
}

static int doSetPowerButtonEnable(int argc, char *argv[])
{
	int dev = 0;
	int val = 0;
	u8 bType = 0;
	u8 out = 0;

	if (argc != 3)
	{
		printf("Invalid number of arguments\n");
		return FAIL;
	}

	dev = doBoardInit(WDT_HW_ADD, &bType);
	if (dev <= 0)
	{
		return FAIL;
	}
	val = readReg8(dev, I2C_CHARGE_STAT_ADD);
	if ( (val & 0xf0) <= 0x10)
	{
		printf("Not available on this firmware version!\n");
		return FAIL;
	}
	val = atoi(argv[2]);

	if (val > 0)
	{
		out = 1;
	}

	return writeReg8(dev, I2C_POWER_SW_USAGE_ADD, out);
}

int main(int argc, char *argv[])
{
	// no argument
	if (argc == 1)
	{
		printf("%s\n", usage);
		return FAIL;
	}

	// Help
	if (0 == strcasecmp(argv[1], "-h") || 0 == strcasecmp(argv[1], "-help"))
	{
		doHelp(argc, argv);
		return OK;
	}

	// Warranty
	if (0 == strcasecmp(argv[1], "-warranty"))
	{
		printf("%s\n", warranty);
		return OK;
	}

	if (0 == strcasecmp(argv[1], "-v") || 0 == strcasecmp(argv[1], "-version"))
	{
		printf("Watchdog Control Software ver %s\n", WDT_SOFTWARE_VER_STR);
		printf("Copyright (c) 2016-2019 Sequent Microsystems\n");
		return OK;
	}

	if (0 == strcasecmp(argv[1], "-r") || 0 == strcasecmp(argv[1], "-reload"))
	{
		return doReload(argc, argv);
	}

	if (0 == strcasecmp(argv[1], "-d") || 0 == strcasecmp(argv[1], "-default"))
	{
		return doDefault(argc, argv);
	}

	if (0 == strcasecmp(argv[1], "-p") || 0 == strcasecmp(argv[1], "-period"))
	{
		return doPeriod(argc, argv);
	}

	if (0 == strcasecmp(argv[1], "-off")
		|| 0 == strcasecmp(argv[1], "-offinterval"))
	{
		return doSetOffTime(argc, argv);
	}

	if (0 == strcasecmp(argv[1], "-c") || 0 == strcasecmp(argv[1], "-clear"))
	{
		return doClear(argc, argv);
	}

	if (0 == strcasecmp(argv[1], "-g") || 0 == strcasecmp(argv[1], "-get"))
	{
		int i = doGet(argc, argv);
		if (i == FAIL)
		{
			return i;
		}
		printf("%d\n", i);
		return OK;
	}
	if (strcasecmp(argv[1], "-rob") == 0
		|| strcasecmp(argv[1], "-repoweronbattery") == 0)
	{
		return doSetRepowerOnBattery(argc, argv);
	}
	if (strcasecmp(argv[1], "-pbe") == 0
		|| strcasecmp(argv[1], "-powerbuttonenable") == 0)
	{
		return doSetPowerButtonEnable(argc, argv);
	}
	printf("Invalid argument(s)!\n");
	printf("%s\n", usage);
	return FAIL;
}
