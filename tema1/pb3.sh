#!/bin/bash

ora=$(date +%H)
echo "$ora"
if [ "$ora" -ge 6 ] && [ "$ora" -lt 12 ];
then
	echo "Buna dimi, $USER!"

elif [ "$ora" -ge 12 ] && [ "$ora" -lt 18 ]; 
then 	
	echo "Buna ziua, $USER!"

elif [ "$ora" -ge 18 ] && [ "$ora" -lt 22 ]; 
then	
	echo "Buna seara, $USER!"

elif ([ "$ora" -ge 22 ] && [ "$ora" -lt 0 ]) || ([ "$ora" -ge 0 ] && [ "$ora" -lt 6 ]); 
then
	echo "Noapte buna, $USER!"
fi

