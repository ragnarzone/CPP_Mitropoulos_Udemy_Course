#include <cstring>
#include <iostream>
#include "CustomString.h"

// no-args constructor
CustomString::CustomString() : str{ nullptr } {
	str = new char[1];
	*str = '\0';
}

// overloaded constructor
CustomString::CustomString(const char* s) : str{ nullptr } {
	if (s == nullptr) {
		str = new char[1];
		*str = '\0';
	}
	else {
		str = new char[std::strlen(s) + 1];
		std::strcpy(str, s);
	}
}

// copy constructor
CustomString::CustomString(const CustomString& source) : str{ nullptr } {
	str = new char[std::strlen(source.str) + 1];
	std::strcpy(str, source.str);
}

// destructor
CustomString::~CustomString() {
	delete[] str;
}

// display method
void CustomString::display() const {
	std::cout << str << " : " << get_length() << std::endl;
}

// length getter
int CustomString::get_length() const {
	return std::strlen(str);
}

// string getter
const char* CustomString::get_str() const {
	return str;
}