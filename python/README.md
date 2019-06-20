# wdt

This is the python library to control [Watchdog for Raspberry Board](https://www.sequentmicrosystems.com/)

## Install

```bash
~$ sudo apt-get update
~$ sudo apt-get install build-essential python-pip python-dev python-smbus git
~$ git clone https://github.com/SequentMicrosystems/wdt-rpi.git
~$ cd wdt-rpi/python/megaio/
~/wdt-rpi/python/wdt$ sudo python setup.py install
```
## Update

```bash
~$ cd wdt-rpi/
~/wdt-rpi$ git pull
~$ cd wdt-rpi/python/megaio/
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
270000
>>>
```
Prototypes for all functions can be found in README.md file locate under wdt-rpi/python/wdt/ directory. 

This library works with both Python2.x and Python3
