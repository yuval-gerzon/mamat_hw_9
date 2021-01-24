#!/bin/bash

while read rule
do
	filtered=""
	rule=`echo "$rule" | tr -d ' ' | tr -d '\n' |sed -e 's/#.*//'`
	if [[ "$rule" == "" ]]; then
		continue
	fi
	
	arrIn=(${rule//,/ })

	for item in "${arrIn[@]}"
	do
		filtered+=`./firewall.exe "$item" < $1`
		filtered+="\n"
	done
	
	total+=`echo -e "${filtered}" | sed '/^$/d' | sort | uniq -c  | grep -E "^ *${#arrIn[@]} " | sed -e "s/^ *${#arrIn[@]} //"`
	total+="\n"

 done

	echo -e "${total}" | sed '/^$/d' | tr -d ' ' | sort
