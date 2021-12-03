#!/bin/bash

#Read the battery voltage
var1=$(wdt -g vb)
#Set the voltage threshold in millivolts
var2=4000
date1=$(date -u)
logfile=/opt/wdt/log/wdt.log

if [[ $var1 == *Fail* ]]; then
   echo "WDT Hardware not detected"
   exit 1
fi

#Read the UPS charge state
state=$(wdt -g c)

if [ $(($var1)) -lt $var2 ] && [ $(($state)) -eq 0 ]; then
   
    #Make the wdt not power back on the RPI when on battery
    wdt -rob 0
    #Set the period to a value that allow RPI to finish shutdown until wdt expire
    wdt -p 60
    echo $date1 ": Shutdown (var1: "$(($var1))"/var2: "$var2"):" >> $logfile
    echo $date1 ": Charging State: " $(($state)) >> $logfile
    echo $date1 :" --------------- " >> $logfile
    #Shut down the RPI and will back on when main power is back
    shutdown now
else
    #reload the counter
    wdt -r
fi    
    echo $date1 ": Battery (var1: "$(($var1))"/var2: "$var2"):" >> $logfile
    echo $date1 ": Charging State: " $(($state)) >> $logfile


