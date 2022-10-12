#!/bin/bash

if [ $# -ne 3 ]
then 
	echo "Numar invalid de argumente"
fi

if [ "$2" = "+" ];
then
	echo `expr $1 + $3`
elif [ "$2" = "-" ];
then
	echo `expr $1 - $3`
elif [ "$2" = "/" ];
then
	echo `expr $1 / $3`
elif [ "$2" = "*" ];
then
	echo `expr $1 * $3`
else
	echo "operator invalid"
fi
