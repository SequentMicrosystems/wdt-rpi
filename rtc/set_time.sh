#!/bin/bash
STR=$(timedatectl status)
SUB="synchronized: yes"
case $STR in

  *"$SUB"*)
    echo "Network time present set the RTC"
    string=$(date +%y%m%d%T)
    year=${string:0:2}
    month=${string:2:2}
    day=${string:4:2}
    hour=${string:6:2}
    min=${string:9:2}
    sec=${string:12:2}
    echo $(wdt -rtc $month $day $year $hour $min $sec)
    exit
    ;;
esac
echo "Network time not present use the RTC"
t=$(wdt -g rtc)
sudo date --set "$t"
