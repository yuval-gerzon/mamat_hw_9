#include "string.h"
#include <iostream>
#include <cstring>
#include "ip.h"
#include <stdlib.h>

//Default constructor, does nothing
String::String(){
	length = 0;
	data = NULL;
}

//copy constructor
String::String(const String &str){
	if(str.length == 0){
		length = 0;
		data = NULL;
	}
	else{
		data = new char[str.length + 1];
		length = str.length;
		if(data != NULL){
			strncpy(data, str.data, length + 1);
		}
	}
}

//constructor
String::String(const char *str){
	if(str == NULL){
		length = 0;
		data = NULL;
		return;
	}
	length = strlen(str);
	if(length == 0){
		data = NULL;
	}else{
		data = new char[length + 1];
		if(data != NULL){
			strncpy(data, str, length + 1);
		}
	}
}


// distructor
String::~String(){
	if(data != NULL) {
		delete[] data;
	}
}

//assign operator for refrencing (&)
String& String::operator=(const String &rhs){
	//delete old string
	if(data != NULL) {
		delete[] data;
		length = 0; //maybe not needed
	}
		if(rhs.length == 0){
			data = NULL;
		}
		else{
			length = rhs.length;
			data = new char[length+1];//maybe +1 not needed
			strncpy(data,rhs.data,length);
		}
	
	return *this;
}

//assign operator for string*
String& String::operator=(const char *str){
	if(data != NULL) {
		delete[] data;
		length = 0; //maybe not needed
	}
		length = strlen(str);
		if(length == 0){
			data = NULL;
		}
		else{
			data = new char[length+1];//maybe +1 not needed
			
			strncpy(data,str,length);
		}
	return *this;
}

//check if equal for ref (&)
bool String::equals(const String &rhs) const {
	if(length != rhs.length){
		return false;
	}

	if(strncmp(data, rhs.data, length) != 0){
		return false;
	}

	return true;
}

//check if equal for point (*)
bool String::equals(const char *rhs) const {
	if(rhs == NULL)
	{
		return false;
	}

	if(length != strlen(rhs)){
		return false;
	}
	
	if(strncmp(data, rhs, length) != 0){
		return false;
	}

	return true;
}


void String::split(const char *delimiters, String **output, size_t *size) const {

	if(size == NULL){
		return;
	}
	if(output == NULL){
	*size = 2;
	return;
	}

	int i = 0;
	int j = 0;
	int k = 0;
	int start_of_word=0;
	int counter = 0;
	int size_of_delim = strlen(delimiters);
	int actual_strings=0;
	String *temp = new String [(this->length) +2 ]; //maximal size
	
	for (i=0;i< this->length;i++){

		for (k=0;k<size_of_delim;k++){
			if( this->data[i] == delimiters[k] ){
				this->data[i] = '\0';
				temp[counter]= String(&this->data[start_of_word]);//TODO: maybe ()
				counter++;
				start_of_word = i+1;
				break;
			}
		}
	}
	
	temp[counter]= String(&this->data[start_of_word]);
	

	*output = new String[counter + 1];
	
	char empty = '\0';
	int place =0;
	//after changing eveery needed char, here we make the output
	for (j=0;j<counter + 1;j++){
	
		bool equals_re = !temp[j].equals(&empty);
	
		if(!temp[j].equals(&empty)) {
		
			(*output)[place] = String(temp[j]);
			actual_strings ++;
			place ++;
		}
	}
	
	counter ++;
	*size = actual_strings ;
	delete[] temp;
}

String String::trim() const {

if (data == NULL) {
return String();
}
int i = 0;
int j = length-1;
char temp [length+1] ={0};
//get the first char that isnt ' '
while ( data[i] == ' ') {
i++;
}
//get the last char that isnt ' '
while ( data[j] == ' ') {
j--;
}
int actual_len = j-i +1;
strncpy(temp,&data[i],actual_len);
//close the last string
temp[actual_len + 1] = '\0';

return String(temp);
}


int String::to_integer() const { 
return atoi(data);
}
