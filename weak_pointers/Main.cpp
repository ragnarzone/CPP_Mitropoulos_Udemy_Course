// Weak pointers in C++

#include <iostream>
#include <memory>

class B;  // this is forward declaration

class A {
	std::shared_ptr<B> b_ptr;
public:
	void set_B(std::shared_ptr<B>& b) {
		b_ptr = b;
	}
	A() {
		std::cout << "A constructor" << std::endl;
	}
	~A() {
		std::cout << "A destructor" << std::endl;
	}
};

class B {
	std::weak_ptr<A> a_ptr; 
public:
	void set_A(std::shared_ptr<A>& a) {
		a_ptr = a;
	}
	B() {
		std::cout << "B Constructor" << std::endl;
	}
	~B() {
		std::cout << "B Destructor" << std::endl;
	}
};


int main() {
	std::shared_ptr<A> a = std::make_shared<A>();
	std::shared_ptr<B> b = std::make_shared<B>();
	a->set_B(b);
	b->set_A(a);

	return 0;
}