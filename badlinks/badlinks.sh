#!/bin/sh
rec_func () {
	for f in "$1"/*
	do
	if [ -d "$f" ] 
			then rec_func "$f"; 
		fi
		if [ -L "$f" -a ! -e "$f" -a $(( `date +%s -r "$f"` + 0)) -lt $(( `date +%s` - 7*24*60*60 )) ]
			then echo "$f"
		fi
	done	
}

if [ -d "$1" ]
	then rec_func "$1"
	else echo "Isn't a dir"
fi
