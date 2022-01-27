# Safe shutdown example
In this example the super-watchdog monitors the Raspberry Pi power source.
When power fails, it sends a text message, shuts down Raspberry Pi and goes on stand-by.
During stand-by power consumptions is reduced to microamps.
If the battery voltage drops below the safe limit, the watchdog shuts down completelly. 
When power comes back up, the watchdog repowers the Raspberry Pi and sends another text message.

## Hardware components:
 - Raspberry PI (2, 3, 4, Zero, Zero 2)
 - [Super Watchdog HAT with Battery Backup for Raspberry Pi](https://sequentmicrosystems.com/collections/all-io-cards/products/raspberry-pi-battery-backup)

## Software setup:
- Install python3 library for super-watchdog:
```bash
~$ sudo apt-get update
~$ sudo apt-get install build-essential python3-pip python3-dev python3-smbus
~$ git clone https://github.com/SequentMicrosystems/wdt-rpi.git
~$ cd wdt-rpi/python/wdt/
~/wdt-rpi/python/wdt$ sudo python3 setup.py install
```

- Register a Twilio account, more info [here](https://raspberrypi-guide.github.io/programming/send-sms-messages)

- Install Twilio python3 library:
```bash
~$ sudo pip3 install twilio
```

- Copy the python script to home folder:
```bash
~$ cp /home/pi/wdt-rpi/examples/power_SMS/power_notify.py /home/pi/
```

- Edit the python script and replace twilio Account SID, Token, Phone Sender from [twilio.com/console](https://www.twilio.com/login?g=%2Fconsole%3F&t=2b1c98334b25c1a785ef15b6556396290e3c704a9b57fc40687cbccd79c46a8c). Fill up your phone number in the TWILIO_PHONE_RECIPIENT variable.  
```bash
~$ nano /home/pi/power_notify.py
```

- Create a launcher script
```bash
~$ nano /home/pi/crontab_start.sh
```

- Fill it with the following lines and save it:
```bash
#!/bin/sh
# crontab_start.sh

sudo python3 /home/pi/power_notify.py &
```

- Give the script executions rights:
```bash
sudo chmod +x /home/pi/crontab_start.sh
```

- Add the crontab task
```bash
sudo crontab -e
```
 This will brings up a crontab window.

 Now, enter the line:
```bash
@reboot sh /home/pi/crontab_start.sh >/home/pi/cronlogs 2>&1
```
 This will start the script each boot-up and write the errors in ```/home/pi/cronlogs```

- Reboot the raspberry
```bash
sudo reboot
```


  
