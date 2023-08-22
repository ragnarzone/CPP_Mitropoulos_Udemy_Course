// Smart pointers in C++

#include <iostream>
#include <memory>

class Test {
private:
	int data;
public:
	Test() : data{ 0 } {
		std::cout << "Test constructor (" << data << ")" << std::endl;
	}
	Test(int data) : data{ data } {
		std::cout << "Test constructor (" << data << ")" << std::endl;
	}
	int get_data() const {
		return data;
	}
	~Test() {
		std::cout << "Test destructor (" << data << ")" << std::endl;
	}
};

int main() {
	//Test* t1 = new Test{ 1000 };
	//delete t1;

	std::unique_ptr<Test> t1{ new Test{100} };
	std::unique_ptr<Test> t2 = std::make_unique<Test>(1000);

	std::unique_ptr<Test> t3;  // this is initialized but points nowhere since it is object initialization
	//t3 = t1; // cannot do this since using unique pointer
	t3 = std::move(t1); // can do this since unique pointer stil valid but moved to another variable
	if (!t1) {  // check if t1 pointer now points nowhere
		std::cout << "t1 is nullptr" << std::endl;
	}

	return 0;
}