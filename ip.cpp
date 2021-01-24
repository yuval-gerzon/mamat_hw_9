#include "ip.h"
#include <cstring>
#include <iostream>

Ip::Ip(String pattern): Field(pattern, IP) {
	//gets contructor from father
}


bool Ip::set_value(String val){
	String* substrs;
	size_t size = 0;
	int temp_ip[4] = {0};
	unsigned int ip;
	unsigned int max_int = 0xFFFFFFFF;
	//in orde to avoid mistakes later on, we used unsigned
	int mask;
	String* parsed_string;
	size_t elements_in_range = 0;

	//the val should be XXX.XXX.XXX.XXX/mask
	val.trim().split("/", &substrs, &size);
	if(2 != size)
	{
		/* if size == 0 then substr was not allocated */
		if(size){
			delete[] substrs;
		}
		return false;
	}
	substrs[0].trim().split(".", &parsed_string, &elements_in_range);
	if(elements_in_range!=4){
	
		if(elements_in_range){
			delete[] parsed_string;
		}
		return false;
	}
	temp_ip[0] = parsed_string[0].trim().to_integer();
	temp_ip[1] = parsed_string[1].trim().to_integer();
	temp_ip[2] = parsed_string[2].trim().to_integer();
	temp_ip[3] = parsed_string[3].trim().to_integer();
	
	ip = ((temp_ip[0])<<24) | ((temp_ip[1])<<16) | ((temp_ip[2])<<8) | ((temp_ip[3]));


	mask = substrs[1].trim().to_integer();

	delete[] substrs;

	if((mask < 0) || (mask > 32)) {
	delete[] parsed_string;
		return false;
	}

	low = (ip>>(32-mask));
	low = (low<<(32-mask));

	if (mask == 32){ 
	high = low; }
	else { high = low | (max_int << mask >>mask);}

	delete[] parsed_string;
	return true;
}

bool Ip::match_value(String val) const {

	bool ind_1, ind_2; //used as flags
	int temp_ip[4] = {0};
	unsigned int ip;
	size_t elements_in_range;
	String* parsed_string;
	
	val.trim().split(".", &parsed_string, &elements_in_range);
	if(elements_in_range!=4){
		if(elements_in_range){
			delete[] parsed_string;
		}
		return false;
	}
	temp_ip[0] = parsed_string[0].trim().to_integer();
	temp_ip[1] = parsed_string[1].trim().to_integer();
	temp_ip[2] = parsed_string[2].trim().to_integer();
	temp_ip[3] = parsed_string[3].trim().to_integer();
	
	
	ip = ((temp_ip[0])<<24) | ((temp_ip[1])<<16) | ((temp_ip[2])<<8) | ((temp_ip[3]));

	ind_1 = (ip >= low);
	ind_2 = (ip <= high);
	
	delete[] parsed_string;
	return (ind_1 & ind_2);
}
