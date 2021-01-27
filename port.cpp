#include "port.h"
#include <cstdlib>

Port::Port(String pattern): Field(pattern, PORT) {
	//gets contructor from father
}
bool Port::set_value(String val) {

	String* parsed_string;
	size_t elements_in_range = 0;
	val.split("-", &parsed_string, &elements_in_range);
	
	if(elements_in_range != 2)
	{
		if(elements_in_range){
			delete[] parsed_string;
		}
		return false;
	}
	range[0] = parsed_string[0].trim().to_integer();
	range[1] = parsed_string[1].trim().to_integer();

	delete[] parsed_string;
	if(range[0] > range[1]){
		return false;
	}else{
		return true;
	}
}
bool Port::match_value(String val) const {
	int temp_num = val.trim().to_integer();
	bool ind_1, ind_2; //used as flags
	
	ind_1 = (range[0] <= temp_num);
	ind_2 = (range[1] >= temp_num);
	
	return (ind_1 & ind_2); 
}
