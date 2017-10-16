#!/bin/bash

help () {
echo "Usage: $0 -H %HOSTADDRESS% -s {A|B|C|D|..} -w value1 -c value2"
##            0  1     2          3     4         5   6     7   8
echo ""
echo "-H Arduino IP Address"
echo "-s Sensor letter"
echo "-w Warning value, with decimal (e.g. 22.00)"
echo "-c Critical Value, with decimal (e.g. 25.00)"
 }

if [ "$1" == "-h" ]; then
	help
	exit 3
fi

if [ $# -lt 4 ]; then
	echo "No sufficient arguments supplied"
	echo ""
	help
	exit 3
fi

myvalue=$(w3m $2 | grep $4 | cut -f2 -d" " | grep .)

if [ 1 -eq "$(echo "${myvalue} > ${8}" | bc)" ]
then
	echo "CRITICAL! Temperature $myvalue exceed range!"
	exit 2
fi

if [ 1 -eq "$(echo "${myvalue} > ${6}" | bc)" ]
then
	echo "WARNING! Temperature $myvalue exceed range!"
	exit 1
fi

if [[ "$myvalue" =~ ^[0-9]+(\.[0-9]+)?$ ]]
then
echo "OK: temperature $myvalue in range!"
else
echo "UNKNOWN: Host unreachable"
exit 3
fi

exit 0
