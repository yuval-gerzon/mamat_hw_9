#include "field.h"
#include "ip.h"
#include "port.h"
#include "string.h"
#include <iostream>
#include <cstring>

// Default constructor
Field::Field(String pattern, field_type type) {
	this->type = type;
	this->pattern = pattern;
}

// Copy constructor
Field::Field(String pattern){
	this->type = GENERIC;
	this->pattern = pattern;
}

//distructor
Field::~Field() {
}

field_type Field::get_type() const {
	return this->type;
}

//set_value
bool Field::set_value(String val) {
	field_type what_type = this->get_type();
	if(what_type == PORT){
		return ((Port*)this)->set_value(val);
	}
	if(what_type == IP){
		return ((Ip*)this)->set_value(val);
	}
	return false;
}

//match_value
bool Field::match_value(String val) const {
	field_type what_type = this->get_type();
	if(what_type == PORT){
		return ((Port*)this)->match_value(val);
	}
	if(what_type == IP){
		return ((Ip*)this)->match_value(val);
	}

	return false;
}

//match(String packet)
bool Field::match(String packet) {
	size_t cur_size;
	int i;
	String* after_split_pack;
	String* after_split_rule;
	size_t num_of_elem;
	packet.split(",", &after_split_pack, &num_of_elem);
	if((!num_of_elem)/*||(num_of_elem>4)*/){
		delete[] after_split_pack;
		return false;
	}
	for(i = 0; i < num_of_elem; i++){
		after_split_pack[i].split("=", &after_split_rule, &cur_size);
		if(cur_size == 2){
			if(pattern.trim().equals(after_split_rule[0].trim())){
				if(match_value(after_split_rule[1].trim())){
					delete[] after_split_rule;
					delete[] after_split_pack;
					return true;
				};
			}
		}
		delete[] after_split_rule;
	}
	delete[] after_split_pack;
	return false;
}
