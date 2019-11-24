# wdt

This is the python library to control [Watchdog for Raspberry](https://www.sequentmicrosystems.com).
Below you find the functions prototypes.

## Functions
### getPeriod()
Return the reset period for the watchdog in seconds.

### setPeriod(val)
Set the reset period for the watchdog.

val - reset period in seconds

### reload()
Reload the watchdog period.

### setDefaultPeriod(val)
Set the period that will be use after watchdog reset the Raspberry and at power-up.

val - default period in seconds [11, 65000]

This value is saved in non-volatile memory 

### getDefaultPeriod()
Return the default period in seconds or -1 in cas of error.

### setOffInterval(val)
Set the period that will be use to keep Raspberry powered off at the next repower operation.

val - off period in seconds [3, 31*24+3600]

This value is valid until next Raspberry repower operation, then is loaded with default 10 seconds 

### getOffInterval()
Return the current Off period in seconds or -1 in cas of error.

### getResetCount()
Return the number of resets performed by the board or -1 in cas of error.  

### getVin()
Return the voltage applied to the board or -1 in cas of error, 

### getVrasp()
Return the voltage applied to the Raspberry Pi or -1 in cas of error

### getVbat()
Return the battery voltage or -1 in cas of error. 

### getTemp()
Return the board temperature deg C or -1 in cas of error.

### getChargeStat()
Return the battery charge status (0 - off, 1 - charge complete, 2 - charging, 3 - fault) or -1 in cas of error.