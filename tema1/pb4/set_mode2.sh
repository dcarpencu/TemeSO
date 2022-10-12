#!/bin/bash

for file in /Users/carpencudavid/POLI/an3/SO/tema1/$1/*.txt ; do
    echo "$file"

case "$2" in
"r")	chmod 400 $file;; 
"w")	chmod 200 $file;;
"x")	chmod 100 $file;;
esac
done
