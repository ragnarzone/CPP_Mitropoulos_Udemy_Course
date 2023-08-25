// Unscoped enumerations in C++

#include <iostream>
#include <vector>
#include <string>

enum Direction {North, South, East, West};

std::string direction_to_string(Direction direction) {
	std::string result;
	switch (direction) {
	case North:
		result = "North";
		break;
	case South:
		result = "South";
		break;
	case East:
		result = "East";
		break;
	case West:
		result = "West";
		break;
	default:
		result = "Unknown direction";
	}
	return result;
}

void test1() {
	Direction direction{ North };
	std::cout << "\nDirection " << direction << std::endl;
	std::cout << direction_to_string(direction) << std::endl;

	direction = West;
	std::cout << "\nDirection " << direction << std::endl;
	std::cout << direction_to_string(direction) << std::endl;
}

int main() {
	test1();

	return 0;
}