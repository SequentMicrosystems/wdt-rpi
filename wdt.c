#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wdt.h"

#define WDT_SOFTWARE_VER_STR  "1.01"


#define WDT_HW_ADD 0x30
#define WDT_RELOAD_KEY  0xCA
#define WDT_RESET_COUNT_KEY	0xBE

#define WDT_DEFAULT_PERIOD_MIN  11
#define WDT_DEFAULT_PERIOD_MAX  64999
#define WDT_PERIOD_MAX  0xffff

char *usage = "Usage:	wdt -h/-help <command>\n"
    "         wdt -warranty\n"
		"         wdt -r/-reload\n"
		"         wdt -d/-default <value>\n"
		"         wdt -p/-period <value>\n"
    "         wdt -g/-get <option>\n"
    "         wdt -c/-clear\n"
    "         wdt -v/-version\n"
		"Type wdt -h <command> for more help";// No trailing newline needed here.
    
char *warranty ="	       Copyright (c) 2016-2019 Sequent Microsystems\n"
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
	if(argc == 3)
	{
    if (strcasecmp (argv [2], "-warranty"    ) == 0)	
		{ 
			printf("\t-warranty:      Display the warranty\n");
			printf("\tUsage:       wdt -warranty\n");
			printf("\tExample:     wdt -warranty\n"); 
		}
		else if (strcasecmp (argv [2], "-r") == 0 || strcasecmp (argv [2], "-reload") == 0)	
		{ 
			printf("\t-r/-reload:       Reload the timer, prevent raspberry to be repowered\n");
			printf("\tUsage:       wdt -r\n");
			printf("\tExample:     wdt -r\n"); 
		}
		else if (strcasecmp (argv [2], "-d") == 0 || strcasecmp (argv [2], "-default") == 0)	
		{ 
			printf("\t-d/-default:       Set the default period (sec), the wdt board automaticaly reload this period after reset\n");
			printf("\tUsage:       wdt -d <value>\n");
			printf("\tUsage:       wdt -default <value>\n");
			printf("\tExample:     wdt -d 270 Set the default period to 270 seconds \n"); 
		}
		else if (strcasecmp (argv [2], "-p") == 0 || strcasecmp (argv [2], "-period") == 0)	
		{ 
			printf("\t-p/-period:  Set the current period and reload the timer\n");
			printf("\tUsage:       wdt -p <value>\n");
			printf("\tExample:     wdt -p 20 Set the wdt period to 20 sec and reload the timer\n"); 
		}
    else if (strcasecmp (argv [2], "-c") == 0 || strcasecmp (argv [2], "-clear") == 0)	
		{ 
			printf("\t-c/-clear:   Clear the reset counter  \n");
			printf("\tUsage:       wdt -c\n");
			printf("\tExample:     wdt -c\n"); 
		}
    else if (strcasecmp (argv [2], "-g") == 0 || strcasecmp (argv [2], "-get") == 0)	
		{ 
			printf("\t-g/-get:      \tGet various parameters\n");
			printf("\tUsage:        \twdt -g <option>\n");
      printf("\t<option>:     \td/default = default period\n\t\t\tp/period = period\n\t\t\tr/resets = total number of resets performed by the board\n");
			printf("\tExample:      \twdt -g d get the wdt default period \n");
		}
		else
		{
			printf("Invalid command!\n");
			printf("%s: %s\n", argv [0], usage);
		}
	}
	else
	{
		printf("%s: %s\n", argv [0], usage);
	}
}


static int doReload(int argc, char* argv[])
{
  int dev = 0;
  UNUSED(argv);
  
  if(argc != 2)
  {
    printf("Invalid number of arguments\n");
    return FAIL;
  }
  
  dev = doBoardInit(WDT_HW_ADD);
  if(dev <= 0)
  {
    return FAIL;
  }
  return writeReg8(dev, I2C_WDT_RELOAD_ADD, WDT_RELOAD_KEY);
}

static int doDefault(int argc, char* argv[])
{
  int dev = 0;
  int val = 0;
  
  if(argc != 3)
  {
    printf("Invalid number of arguments\n");
    return FAIL;
  }
  
  dev = doBoardInit(WDT_HW_ADD);
  if(dev <= 0)
  {
    return FAIL;
  }
  val = atoi(argv[2]);
  if((WDT_DEFAULT_PERIOD_MIN <= val) && (val <= WDT_DEFAULT_PERIOD_MAX))
  {
    return writeReg16(dev, I2C_WDT_INIT_INTERVAL_SET_ADD, val);
  }
  return FAIL;
}

static int doPeriod(int argc, char* argv[])
{
  int dev = 0;
  int val = 0;
  
  if(argc != 3)
  {
    printf("Invalid number of arguments\n");
    return FAIL;
  }
  
  dev = doBoardInit(WDT_HW_ADD);
  if(dev <= 0)
  {
    return FAIL;
  }
  val = atoi(argv[2]);
  if((0 < val) && (val <= WDT_PERIOD_MAX))
  {
    return writeReg16(dev, I2C_WDT_INTERVAL_SET_ADD, val);
  }
  return FAIL;
}

static int doClear(int argc, char* argv[])
{
  int dev = 0;
  
  UNUSED(argv);
  
  if(argc != 2)
  {
    printf("Invalid number of arguments\n");
    return FAIL;
  }
  
  dev = doBoardInit(WDT_HW_ADD);
  if(dev <= 0)
  {
    return FAIL;
  }
 
  return writeReg16(dev, I2C_WDT_CLEAR_RESET_COUNT_ADD, WDT_RESET_COUNT_KEY);
}


static int doGet(int argc, char* argv[])
{
  int dev = 0;
  int val = 0;
  
  if(argc != 3)
  {
    printf("Invalid number of arguments\n");
    return FAIL;
  }
  
  dev = doBoardInit(WDT_HW_ADD);
  if(dev <= 0)
  {
    return FAIL;
  }
  
  if(strcasecmp(argv[2], "d") == 0 || strcasecmp(argv[2], "default") == 0)
  {
    val = readReg16(dev, I2C_WDT_INIT_INTERVAL_GET_ADD);
  }
  else if(strcasecmp(argv[2], "p") == 0 || strcasecmp(argv[2], "period") == 0)
  {
    val = readReg16(dev, I2C_WDT_INTERVAL_GET_ADD);
  }
  else if(strcasecmp(argv[2], "r") == 0 || strcasecmp(argv[2], "resets") == 0)
  {
    val = readReg16(dev, I2C_WDT_RESET_COUNT_ADD);
  }
  else
  {
    printf ("Invalid  option for -get command\n");
    return FAIL;
  }
  return val;
}


int main(int argc, char *argv [])
{  
  // no argument
  if (argc == 1)
  {
    printf( "%s\n", usage) ;
    return FAIL ;
  }
 
  // Help
  if (0 == strcasecmp (argv [1], "-h") ||  0 == strcasecmp (argv [1], "-help"))
  {
    doHelp(argc, argv);
    return OK;
  }
  
  // Warranty
  if (0 == strcasecmp (argv [1], "-warranty"))
  {
    printf("%s\n", warranty);
    return OK;
  }
  
  if (0 == strcasecmp (argv [1], "-v") ||  0 == strcasecmp (argv [1], "-version"))
  {
    printf("Watchdog Control Software ver %s\n", WDT_SOFTWARE_VER_STR);
    printf("Copyright (c) 2016-2019 Sequent Microsystems\n");
    return OK;
  }
  
  if(0 == strcasecmp(argv[1], "-r") || 0 == strcasecmp(argv[1], "-reload"))
  {
    return doReload(argc, argv);
  }
  
  if(0 == strcasecmp(argv[1], "-d") || 0 == strcasecmp(argv[1], "-default"))
  {
    return doDefault(argc, argv);
  }
  
  if(0 == strcasecmp(argv[1], "-p") || 0 == strcasecmp(argv[1], "-period"))
  {
    return doPeriod(argc, argv);
  }
  
  if(0 == strcasecmp(argv[1], "-c") || 0 == strcasecmp(argv[1], "-clear"))
  {
    return doClear(argc, argv);
  }
  
  if(0 == strcasecmp(argv[1], "-g") || 0 == strcasecmp(argv[1], "-get"))
  {
    int i = doGet(argc, argv);
    if (i == FAIL)
    {
      return i;
    }
    printf("%d\n", i);
    return OK;
  }
  printf("Invalid argument(s)!\n");
  printf( "%s\n", usage);
  return FAIL;
}
