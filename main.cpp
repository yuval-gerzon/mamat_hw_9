#include <iostream>
#include <cstring>
#include "ip.h"
#include "port.h"
#include "input.h"

int main(int argc, char** argv){

	String* rule_parts;
	size_t size = 0;
	
	if( check_args(argc, argv) ) {
		return 1;
	}
	
	String rule(argv[1]);
    rule.split("=", &rule_parts, &size);
	
	bool ind_1 = rule_parts[0].trim().equals("src-ip");
	bool ind_2 = rule_parts[0].trim().equals("dst-ip");
	bool ind_3 = rule_parts[0].trim().equals("dst-port");
	bool ind_4 = rule_parts[0].trim().equals("src-port");
	
	//IP
	if(ind_1 | ind_2){
		Ip ipFilter(rule_parts[0].trim()); 
		ipFilter.set_value(rule_parts[1].trim()); 
		parse_input(ipFilter);
	}

	//PORT
	if(ind_3 | ind_4 ){
		Port portFilter(rule_parts[0].trim()); 
		portFilter.set_value(rule_parts[1].trim()); 

		parse_input(portFilter); 
	}
	delete[] rule_parts;
}
