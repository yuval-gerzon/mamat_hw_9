#!/bin/bash

final_result=""
while read packet
do
	while read rule
	do
		filtered=""
		rule=`echo "$rule" |sed -e 's/#.*//'| tr -d ' ' | tr -d '\n'`
		if [[ "$rule" == "" ]]; then
			continue
		fi
		
		arrIn=($(echo $rule|tr -d ","))
		

		for item in "${arrIn[@]}"
		do
			filtered+=`echo "$packet" | ./firewall.exe "$item"`
			filtered+="\n"
		done
		
		final_result+=`echo -e "${filtered}" | sed '/^$/d' | sort | uniq -c  | grep -E "^ *${#arrIn[@]} " | sed -e "s/^ *${#arrIn[@]} //"`
		final_result+="\n"

	 done < "$1"
done

	echo -e "${final_result}" | sort | sed '/^$/d' | tr -d ' '