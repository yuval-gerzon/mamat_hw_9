#!/bin/bash

final_result=""
while read packet
do
	while read rule
	do
		filtered=""
		#clean rule
		rule=`echo "$rule" | tr -d ' ' | sed -e 's/#.*//'`
		#skip empty
		if [[ "$rule" == "" ]]; then
			continue
		fi
		#append rule
		readarray -d , -t rules_finals <<< "$rule"
		#use rules
		for rule_final in "${rules_finals[@]}"
		do
			filtered+=`echo "$packet" | ./firewall.exe "$rule_final"`
			filtered+="\n"
		done

		current_line=`echo -e "${filtered}" | sed '/^$/d' | wc -l`
		#check if ended
		if [[ ${#rules_finals[@]} == $current_line ]]; then

				final_result+=`echo -e "${filtered}"`
				final_result+="\n"
			break
		fi

	 done < "$1"

done
	#get it out in the order required in 'chidodim' by alon (sort and uniq first)
	echo -e "${final_result}" | sort | uniq | sed '/^$/d' | tr -d ' '