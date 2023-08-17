#include <iostream>
#include <vector>
#include "CustomString.h"

int main() {
	CustomString a{ "Hello" };
	CustomString b;
	b = a;  // b.operator=(a)
	b = "This is a test";

	return 0;
}