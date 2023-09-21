// stateful lambdas
#include <iostream>
#include <vector>
#include <algorithm>

int global_x{ 1000 };

// capture by value
// the global variables cannot be captured because it is not
// within the scope of the lambda
// but it can be accessed from within the lambda using normal name lookup rules

void test1() {
	std::cout << "\nTest1 ==========================" << std::endl;

	int local_x{ 100 };

	auto l = [local_x]() {
		std::cout << local_x << std::endl;
		std::cout << global_x << std::endl;
	};
	l();
}

// capture by value - mutable
// captured variable can only be modified within the lambda
// by using the mutable keyword
// in this case only copied value will be modified
void test2() {
	std::cout << "\nTest2 =======================" << std::endl;

	int x{ 100 };

	auto l = [x]() mutable {
		x += 100;
		std::cout << x << std::endl;
	};

	l(); // increments by 100 equals 200
	std::cout << x << std::endl;

	l(); // increments by 100 equals 300
	std::cout << x << std::endl;
}

// capture by reference
// any changes made in body of lambda will change the actual variable
void test3() {
	std::cout << "\nTest3 ==========================" << std::endl;

	int x{ 100 };

	auto l = [&x]() mutable {
		x += 100;
		std::cout << x << std::endl;
	};

	l();
	std::cout << x << std::endl;
}

// default capture by value - mutable
// only variables used within the lambda body are captured by value
void test4() {
	std::cout << "\nTest4 ============================" << std::endl;

	int x{ 100 };
	int y{ 200 };
	int z{ 300 }; // should produce an "unused variable" warning when compiling

	auto l = [=]() mutable {
		x += 100;
		y += 100;
		std::cout << x << std::endl;
		std::cout << y << std::endl;
	};
	l();

	std::cout << "\n";
	std::cout << x << std::endl;
	std::cout << y << std::endl;
}

// default capture by reference
void test5() {
	std::cout << "\nTest5 ==================" << std::endl;

	int x{ 100 };
	int y{ 200 };
	int z{ 300 };

	auto l = [&]() {
		x += 100;
		y += 100;
		z += 100;
		std::cout << x << std::endl;
		std::cout << y << std::endl;
		std::cout << z << std::endl;
	};

	l();
	
	std::cout << "\n";
	std::cout << x << std::endl;
	std::cout << y << std::endl;
	std::cout << z << std::endl;
}

// default capture by value, capture 'y' by reference
void test6() {
	std::cout << "\nTest6 ============================" << std::endl;

	int x{ 100 };
	int y{ 200 };
	int z{ 300 };

	auto l = [=, &y]() mutable {
		x += 100;
		y += 100;
		z += 100;

		std::cout << x << std::endl;
		std::cout << y << std::endl;
		std::cout << z << std::endl;
	};

	l();

	std::cout << "\n";
	std::cout << x << std::endl;
	std::cout << y << std::endl;
	std::cout << z << std::endl;
}

// default capture by reference, capture x and z by value
void test7() {
	std::cout << "\nTest7 =========================" << std::endl;

	int x{ 100 };
	int y{ 200 };
	int z{ 300 };

	auto l = [&, x, z]() mutable {
		x += 100;
		y += 100;
		z += 100;
		std::cout << x << std::endl;
		std::cout << y << std::endl;
		std::cout << z << std::endl;
	};
	l();

	std::cout << "\n";
	std::cout << x << std::endl;
	std::cout << y << std::endl;
	std::cout << z << std::endl;
}

// class used for test8
class Person {
	friend std::ostream& operator<<(std::ostream& os, const Person& rhs);
private:
	std::string name;
	int age;
public:
	Person() = default;
	Person(std::string name, int age) : name{ name }, age{ age }{}
	Person(const Person& p) = default;
	~Person() = default;
	std::string get_name() const { return name; }
	void set_name(std::string name) { this->name = name; }
	int get_age() const { return age; }
	void set_age(int age) { this->age = age; }

	auto change_person1() { return [this](std::string new_name, int new_age) {name = new_name; age = new_age; }; }
	auto change_person2() { return [=](std::string new_name, int new_age) {name = new_name; age = new_age; }; }
	auto change_person3() { return [&](std::string new_name, int new_age) {name = new_name; age = new_age; }; }
};

std::ostream& operator<<(std::ostream& os, const Person& rhs) {
	os << "[Person: " << rhs.name << " : " << rhs.age << "]";
	return os;
}

// default capture by reference of the current object using [this]
// [=], [&], [this] are equivalent when capturing an objects member variables - all are captured by reference
// C++20 allows [*this], which captures by value
void test8() {
	std::cout << "\nTest8 ==========================" << std::endl;

	Person person("Larry", 18);
	std::cout << person << std::endl;

	// default capture [this]
	auto change_person1 = person.change_person1();
	change_person1("Moe", 30);
	std::cout << person << std::endl;

	// default capture [=]
	auto change_person2 = person.change_person2();
	change_person1("Curly", 25);
	std::cout << person << std::endl;

	// default capture [&]
	auto change_person3 = person.change_person1();
	change_person3("Dmitrii", 28);
	std::cout << person << std::endl;
}

class Lambda {
private:
	int y;
public:
	Lambda(int y) : y{ y } {};

	void operator()(int x) const {
		std::cout << x + y << std::endl;
	};
};

void test9() {
	std::cout << "\nTest9 ===========================" << std::endl;

	int y{ 100 };

	Lambda lambda1(y);
	auto lambda2 = [y](int x) {std::cout << x + y << std::endl; };

	lambda1(200);
	lambda2(200);
}

class People {
	std::vector<Person> people;
	int max_people;
public:
	People(int max = 10) : max_people(max){}
	People(const People& p) = default;
	void add(std::string name, int age) {
		people.emplace_back(name, age);
	}
	void set_max_people(int max) {
		max_people = max;
	}
	int get_max_people() const {
		return max_people;
	}

	// this method return a vector of Person objects in
	// people whose age > max_age and it limits the number of
	// persons returned to be <= the member variable max_people.
	std::vector<Person> get_people(int max_age) {
		std::vector<Person> result;
		int count{ 0 };
		std::copy_if(people.begin(), 
			people.end(), 
			std::back_inserter(result),
			[this, &count, max_age](const Person& p) {return p.get_age() > max_age && ++count <= max_people; }
			);
		return result;
	}
};

void test10() {
	std::cout << "\nTest10 ==========================" << std::endl;

	People friends;
	friends.add("Larry", 18);
	friends.add("Curly", 25);
	friends.add("Moe", 35);
	friends.add("Dmitrii", 28);
	friends.add("James", 65);

	auto result = friends.get_people(17);

	std::cout << std::endl;
	for (const auto& p : result) {
		std::cout << p << std::endl;
	}

	friends.set_max_people(3);
	result = friends.get_people(17);

	std::cout << std::endl;
	for (const auto& p : result) {
		std::cout << p << std::endl;
	}

	result = friends.get_people(50);
	
	std::cout << std::endl;
	for (const auto& p : result) {
		std::cout << p << std::endl;
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
	test8();
	test9();
	test10();

	std::cout << std::endl;
	return 0;
}