#ifndef  _CUSTOMSTRING_H_
#define _CUSTOMSTRING_H_

class CustomString {
private:
	char* str; // pointer to a char[] that holds a C-style string
public:
	CustomString();  // no-args constructor
	CustomString(const char* s);  // overloaded constructor
	CustomString(const CustomString& source);  // copy constructor
	~CustomString();  // destructor
	void display() const;
	int get_length() const;
	const char* get_str() const;

};

#endif // ! _CUSTOMSTRING_H_
