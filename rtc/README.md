# set_time.sh

This is a script created for the Super Watchdog RTC usage.
The script checks if the raspberry clock is synchronized with the network time, if yes it set the card RTC, if not reads the RTC and set the system clock with it.

#### Usage:
```bash
$  sudo /home/pi/wdt-rpi/rtc/set_time.sh
```

The actual PATH might be different depending on your wdt-rpi PATH

The script can be run manually to check and fix the system time or can be run from cron at a few minutes intervals.
