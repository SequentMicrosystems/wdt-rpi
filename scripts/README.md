# Helper Script for Graceful Shutdown of RPi

By default, the script, `ups-debug.sh`, will need to be copied to `/opt/wdt/`

```bash
sudo mkdir -r /opt/wdt
sudo cp ups-debug.sh /opt/wdt
sudo chmod +x /opt/wdt/ups-debug.sh
```

The entry at the bottom of `crontab` is an example, and would be placed in `/etc/crontab`

### What Does this Script Do?

Each time the script is run by cron, the power state is checked as well as the voltage of the battery.  By default, two conditions need to be met inorder for the script to gracefully shutdown your RPi.

1. Voltage is less than 4000mV, and
2. The UPS must be operating on battery power and not receiving power via the barrel-style DC input or the USB DC input

Each time the script runs (default, every five minutes), voltage and charge state are recorded in `/opt/wdt/log/wdt.log`

