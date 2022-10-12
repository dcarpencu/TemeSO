#!/bin/bash

fis="$1"
echo $fis

if [ ${fis: -4} = ".txt" ];
then
	echo "e fisier"
fi
