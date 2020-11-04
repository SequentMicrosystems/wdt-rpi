# wdt

This is the python library to control [Super-Watchdog with Battery Backup for Raspberry Pi](https://sequentmicrosystems.com/product/super-watchdog-for-raspberry-pi/).

## Install

```bash
~$ sudo apt-get update
~$ sudo apt-get install build-essential python-pip python-dev python-smbus git
~$ git clone https://github.com/SequentMicrosystems/wdt-rpi.git
~$ cd wdt-rpi/python/wdt/
~/wdt-rpi/python/wdt$ sudo python setup.py install
```

for Python 3.x usge replace last line with:
```bash
~/wdt-rpi/python/wdt$ sudo python3 setup.py install
```

## Update

```bash
~$ cd wdt-rpi/
~/wdt-rpi$ git pull
~$ cd wdt-rpi/python/wdt/
~/wdt-rpi/python/wdt$ sudo python setup.py install
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
