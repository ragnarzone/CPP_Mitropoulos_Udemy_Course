#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>  // used for std::iota

// for_each - non-modifying sequence operation
void test1() {
	std::cout << "\nTest1 =============================" << std::endl;
	std::vector<int> nums{ 10,20,30,40,50 };

	std::for_each(nums.begin(), nums.end(), [](int num) {
		std::cout << num << " ";
		});
}

// is_permutation - non-modifying sequence operation
// tests whether two triangles are equivalent
// triangles are defined by a vector of three points in any order
// regardles of the order of points, if two triangles contain the same three points
// then they are equivalent
void test2() {
	std::cout << "\n\nTest2 ============================" << std::endl;

	struct Point {
		int x;
		int y;
	};

	Point pt1{ 1,2 };
	Point pt2{ 4,3 };
	Point pt3{ 3,5 };
	Point pt4{ 3,1 };

	std::vector<Point> triangle1{ pt1, pt2, pt3 };
	std::vector<Point> triangle2{ pt2,pt3,pt1 };
	std::vector<Point> triangle3{ pt1,pt2,pt4 };

	// test whether triangle1 and triangle2 are equivalent
	if (std::is_permutation(triangle1.begin(),
		triangle1.end(),
		triangle2.begin(),
		[](Point lhs, Point rhs) {
			return lhs.x == rhs.x && lhs.y == rhs.y;
		})) {
		std::cout << "Triangle1 and Triangle2 are equivalent!" << std::endl;
	}
	else {
		std::cout << "Triangle1 and Triangle2 are not equivalent!" << std::endl;
	}

	// test whether triangle1 and triangle2 are equivalent
	if (std::is_permutation(triangle1.begin(),
		triangle1.end(),
		triangle3.begin(),
		[](Point lhs, Point rhs) {return lhs.x == rhs.x && lhs.y == rhs.y; }
	)) {
		std::cout << "Triangle1 and Triangle3 are equivalent!" << std::endl;
	}
	else {
		std::cout << "Triangle1 and Triangle3 are not equivalent!" << std::endl;
	}
}

void test3() {
	std::cout << "\nTest3 =========================" << std::endl;

	std::vector<int> test_scores{ 93,88,75,68,65 };
	int bonus_points{ 5 };

	std::transform(test_scores.begin(),
		test_scores.end(),
		test_scores.begin(),
		[bonus_points](int score) {return score += bonus_points; }
	);

	// display updated test_scores
	for (int score : test_scores){
		std::cout << score << " ";
	}
}

// remove_if - modifying sequence operator
void test4() {
	std::cout << "\n\nTest4 ===========================" << std::endl;

	std::vector<int> nums{ 1,2,3,4,5 };

	nums.erase(std::remove_if(nums.begin(), nums.end(),
		[](int num) {return num % 2 == 0; }
	), nums.end());

	// display update nums
	for (int num : nums) {
		std::cout << num << " ";
	}
}

// used for test5
class Person {
	friend std::ostream& operator<<(std::ostream& os, const Person& rhs);
private:
	std::string name;
	int age;
public:
	Person(std::string name, int age) : name{ name }, age{ age } {};
	Person(const Person& p) : name{ p.name }, age{ p.age } {};
	~Person() = default;
	std::string get_name() const { return name; }
	void set_name(std::string name) { this->name = name; }
	int get_age() const { return age; }
	void set_age(int age) { this->age = age; }
};

std::ostream& operator<<(std::ostream& os, const Person& rhs) {
	os << "[Person: " << rhs.name << " : " << rhs.age << "]";
	return os;
}

// sort
// sorts elements in the sequence according to the predicate lambda
// in this example, a vector of people is first sorted by name in ascending order
// and then by age in descending order.
void test5() {
	std::cout << "\n\nTest5 ===========================" << std::endl;

	Person person1("Larry", 18);
	Person person2("Moe", 30);
	Person person3("Curly", 25);

	std::vector<Person> people{ person1, person2, person3 };

	// sort people by name in ascending order
	std::sort(people.begin(), people.end(), [](Person lhs, Person rhs) {
		return lhs.get_name() < rhs.get_name();
	});

	for (Person person : people) {
		std::cout << person << std::endl;
	}

	std::cout << "\n";

	// sort people by age in descending order
	std::sort(people.begin(), people.end(), [](Person lhs, Person rhs) {
		return lhs.get_age() > rhs.get_age();
	});

	for (Person person : people) {
		std::cout << person << std::endl;
	}
}

// in_between function is used for test6
// all_of - non-modifying sequence operation
// tests whether all elements contained within the sequence satisfy the 
// condition defined by the passed predicate lambda
bool in_between(const std::vector<int>& nums, int start_value, int end_value) {
	bool result{ false };
	result = std::all_of(nums.begin(), nums.end(), [start_value, end_value](int value) {
		return value >= start_value && value <= end_value;
	});
	return result;
}

void test6() {
	std::cout << "\nTest6 =======================" << std::endl;
	std::cout << std::boolalpha;

	std::vector<int> nums(10);
	std::iota(nums.begin(), nums.end(), 1);

	for (int num : nums) {
		std::cout << num << " ";
	}

	std::cout << std::endl;

	std::cout << in_between(nums, 50, 60) << std::endl;
	std::cout << in_between(nums, 1, 10) << std::endl;
	std::cout << in_between(nums, 5, 7) << std::endl;
}

// the following classes are used for test7
class Password_Validator1 {
private:
	char restricted_symbol{ '$' };
public:
	bool is_valid(std::string password) {
		return std::all_of(password.begin(), password.end(), [this](char character) {
			return character != restricted_symbol;
		});
	}
};

class Password_Validator2 {
private:
	std::vector<char> restricted_symbols{ '!', '$', '+' };
public:
	bool is_valid(std::string password) {
		return std::all_of(password.begin(), password.end(), [this](char character) {
			return std::none_of(restricted_symbols.begin(), restricted_symbols.end(), [character](char symbol) {
				return character == symbol;
			});
		});
	}
};

// all_of - non-modifying sequence operation
// tests whether all elements contained within the sequence satisfy the condition
// defined by the passed predicate lambda
// in this case, the all_of function is contained within the class
// Password_Validator which determines whether a password contains
// a restricted symbol and thus is valid or not.
void test7() {
	std::cout << "\nTest7 =======================" << std::endl;

	// Password_Validator1 ========================
	std::string password{ "holywood1$" };
	Password_Validator1 pv1;

	// test whether password is valid
	if (pv1.is_valid(password)) {
		std::cout << "The password " << password << " is valid!" << std::endl;
	}
	else {
		std::cout << "The password " << password << " is not valid!" << std::endl;
	}
	
	// test whether new password is valid
	password = "hollywood1";
	if (pv1.is_valid(password)) {
		std::cout << "The password " << password << " is valid!" << std::endl;
	}
	else {
		std::cout << "The password " << password << " is not valid!" << std::endl;
	}

	std::cout << "\n";

	// Password_Validator2 =========================
	password = "C++Rocks!";
	Password_Validator2 pv2;

	// test whether passwod is valid
	if (pv2.is_valid(password)) {
		std::cout << "The password " << password << " is valid!" << std::endl;
	}
	else {
		std::cout << "The password " << password << " is not valid!" << std::endl;
	}

	password = "CPlusPlusRocks";
	if (pv2.is_valid(password)) {
		std::cout << "The password " << password << " is valid!" << std::endl;
	}
	else {
		std::cout << "The password " << password << " is not valid!" << std::endl;
	}
}



int main() {
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();

	return 0;
}