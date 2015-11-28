#!/bin/bash
#http://www.akamaras.com/linux/linux-script-to-check-if-a-service-is-running-and-start-it-if-its-stopped/

service=receive.sh

if (( $(ps -ef | grep -v grep | grep $service | wc -l) > 0 ))
then
    echo "$service is running!!!"
else
    sh $service
fi