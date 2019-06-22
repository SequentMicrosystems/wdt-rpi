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
Return the default period in seconds.

### getResetCount()
Return the number of resets performed by the board  
