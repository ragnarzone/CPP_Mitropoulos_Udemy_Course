// Scoped enums in C++

#include <iostream>
#include <vector>

enum class Grocery_Item {Milk=350, Bread=250, Apple=132, Orange=100};

std::ostream& operator<<(std::ostream& os, Grocery_Item grocery_item) {
	std::underlying_type_t<Grocery_Item> value = std::underlying_type_t<Grocery_Item>(grocery_item);
	switch (grocery_item) {
		case Grocery_Item::Milk:
			os << "Milk";
			break;
		case Grocery_Item::Bread:
			os << "Bread";
			break;
		case Grocery_Item::Apple:
			os << "Apple";
			break;
		case Grocery_Item::Orange:
			os << "Orange";
			break;
		default:
			os << "Invalid item";
		}
		os << " : " << value;
		return os;
}

bool is_valid_grocery_item(Grocery_Item grocery_item) {
	switch (grocery_item) {
		case Grocery_Item::Milk:
		case Grocery_Item::Bread:
		case Grocery_Item::Apple:
		case Grocery_Item::Orange:
			return true;
		default:
			return false;
	}
}

void display_grocery_list(const std::vector<Grocery_Item>& grocery_list) {
	std::cout << "Grocery List" << "\n=================================" << std::endl;
	int invalid_item_count{ 0 };
	int valid_item_count{ 0 };
	for (Grocery_Item grocery_item : grocery_list) {
		std::cout << grocery_item << std::endl;

		if (is_valid_grocery_item(grocery_item)) {
			valid_item_count++;
		}
		else {
			invalid_item_count++;
		}
	}

	std::cout << "===============================" << std::endl;
	std::cout << "Valid items: " << valid_item_count << std::endl;
	std::cout << "Invalid items: " << invalid_item_count << std::endl;
	std::cout << "Total items: " << valid_item_count + invalid_item_count << std::endl;
}

void test1() {
	std::cout << "\n--- Test1 -------\n" << std::endl;

	std::vector<Grocery_Item> shopping_list;

	shopping_list.push_back(Grocery_Item::Apple);
	shopping_list.push_back(Grocery_Item::Milk);
	shopping_list.push_back(Grocery_Item::Orange);

	int Helicopter{ 1000 };
	// shopping_list.push_back(Helicopter);  // compile time error
	shopping_list.push_back(Grocery_Item(Helicopter));  // Invalid item
	shopping_list.push_back(Grocery_Item(350));  // Milk

	display_grocery_list(shopping_list);
}

int main() {
	test1();

	return 0;
}