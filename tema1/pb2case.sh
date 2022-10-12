#!/bin/bash

if [ $# -ne 3 ]
then 
	echo "Numar invalid de argumente"
fi

case "$2" in
"+") echo `expr $1 + $3`;;
"-") echo `expr $1 - $3`;;
"*") echo `expr $1 * $3`;;
"/") echo `expr $1 / $3`;;
*) echo "operator invalid";;
esac
