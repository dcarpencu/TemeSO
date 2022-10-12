#!/bin/bash

if [ $# -lt 3 ];
then
	echo "Prea putine argumente"
elif [ $1 -gt $2 ] && [ $1 -gt $3 ];
then	
	echo "Cel mai mare nr este: $1"
elif [ $2 -gt $1 ] && [ $2 -gt $3 ];
then
	echo "Cel mai amre nr este: $2"
else
	echo "Cel mai mare nr este: $3"
fi
