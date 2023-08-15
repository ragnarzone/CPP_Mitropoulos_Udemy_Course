#include <iostream>
#include "CustomString.h"

int main() {
	CustomString empty;
	CustomString larry("Larry");
	CustomString stooge{ larry };

	empty.display();
	larry.display();
	stooge.display();

	return 0;
}