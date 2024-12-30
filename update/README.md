# update

This is the Super Watchdog  Card firmware update tool.

## Usage

```bash
git clone https://github.com/SequentMicrosystems/wdt-rpi.git
cd wdt-rpi/update/
./update
```
or
```bash
./update64
```

If you clone the repository already, skip the first step. 
The command will download the newest firmware version from our server and write it  to the board.
The stack level of the board must be provided as a parameter. 

## Warning
Please make shure that the I2C port is reseved to the update, meaning no program or script tries to access the I2C port during update.
