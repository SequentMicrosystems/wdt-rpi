# wdt

This is the python library to control [Super-Watchdog with Battery Backup for Raspberry Pi](https://sequentmicrosystems.com/collections/all-io-cards/products/raspberry-pi-battery-backup).

## Install

```bash
sudo pip install SMwdt
```

## Usage

Now you can import the wdt library and use its functions. To test, read the default period:

```bash
~$ python
Python 2.7.9 (default, Sep 17 2016, 20:26:04)
[GCC 4.9.2] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> import wdt
>>> wdt.getDefaultPeriod()
270
>>>
```
## [Documentation](https://github.com/SequentMicrosystems/wdt-rpi/blob/master/python/wdt/README.md). 

This library works with both Python2 and Python3
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

### getRepowerOnBattery()
Return the "Repower On Battery" settings: 
 - 0 - if a repower event occur and the main power (external 5V) is not present it will power off entyre watchdog (Wachdog and Raspbery will start only if main power is restored) 
 - 1 - the Watchdog will restore Raspberry at repower event even the main power source is not present.
 
 ### setRepowerOnBattery(val)
 Setter for "Repower On Battery" settings, posible values:
  - 0 - if a repower event occur and the main power (external 5V) is not present it will power off entyre watchdog (Wachdog and Raspbery will start only if main power is restored) 
 - 1 - the Watchdog will restore Raspberry at repower event even the main power source is not present.

### getPowerButtonEnable()
Getter for the power button usage.
returns  - 1 if the int signal Raspberry pi 40 pin connector pin #23 is used as a power button. - 0 if the pin is used to reload the watchdog counter

### setPowerButtonEnable(val)
Setter for power button usage.
If val = 0, disable power button functionality else enable it
The value is written in flash so is persistent.

### getPowerButtonPush()
Getter for power button push status.
Return 1 if the button has been pushed at least once in the current power cycle and 0 else.
The status of the button is cleared when the Raspberry power is restored.
When this status is 1 and Raspberry power is down (watchdog timer expired) remain down until you push the button again. In this way, the power off button can be implemented.
If the user do not wish this feature can disable it (setPowerButtonEnable(0)).

### clrPowerButton()
Clear the power button status. 
This function can be used for prevent false button trigger at Rapberry pi Start-up
Return 1 if succeed, and -1 if fails.

### getPowerButton()
The same as getPowerButtonPush().

### setPowerButton(val)
Set the power button push state so you can emulate the button in software or cleasr his status.
 - val 0/1
Return 1 if succeed, and -1 if fails.


### getPowerButtonInterruptEnable()
Getter for the power button interrupt enable.
returns  - 1 if the interrupt will be generated when button is released, 0 else


### setPowerButtonInterruptEnable(val)
Setter for power button interrupt generation.
If val = 0, disable power button interrupt generation else enable it
The value is written in flash so is persistent.


### getRTC()
Return the RTC date and time as a list
return (year, month, day, hour, minute, seconds)

### setRTC(y, mo, d, h, m, s)
Set the RTC date and time
y - year between 2000..2255 or between 0..255
mo - month 1..12
d - day
h - hour
m - minutes
s - seconds
