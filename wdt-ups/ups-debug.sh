#!/bin/bash

#Read the battery voltage
var1=$(wdt -g vb)
#Set the voltage threshold in millivolts
var2=3400
date1=$(date -u)
logfile=/opt/wdt-ups/log/wdt
if [ $(($var1)) -lt $var2 ]; then
    #Make the wdt not power back on the RPI when on battery
    wdt -rob 0
    #Set the period to a value that allow RPI to finish shutdown until wdt expire
    wdt -p 30
    echo $date1 ": Shutdown (var1: "$var1"/var2: "$var2"):" >> $logfile
    #Shut down the RPI and will back on when main power is back
    shutdown now
else
    #reload the counter
    wdt -r
fi    
    echo $date1 ": Battery (var1: "$var1"/var2: "$var2"):" >> $logfile



