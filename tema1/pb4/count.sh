#!/bin/bash
sum=0;
for file in /Users/carpencudavid/POLI/an3/SO/tema1/$1/*.txt ; do
	ct=`wc -c $file`
	echo ${ct}
	sum=${sum+$ct}	
done
