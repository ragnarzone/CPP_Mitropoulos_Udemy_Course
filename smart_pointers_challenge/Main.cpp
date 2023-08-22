// Smart pointers challenge

#include <iostream>
#include <memory>
#include <vector>

class Test {
private:
	int data;
public:
	Test() : data{ 0 } {
		std::cout << "\tTest constructor (" << data << ")" << std::endl;
	}
	Test(int data) : data{ data } {
		std::cout << "\tTest constructor (" << data << ")" << std::endl;
	}
	int get_data() const {
		return data;
	}
	~Test() {
		std::cout << "\tTest destructor (" << data << ")" << std::endl;
	}
};

// Function prototypes
std::unique_ptr<std::vector<std::shared_ptr<Test>>> make();
void fill(std::vector<std::shared_ptr<Test>>& vec, int num);
void display(const std::vector<std::shared_ptr<Test>>& vec);

int main() {
	std::unique_ptr<std::vector<std::shared_ptr<Test>>> vec_ptr;
	vec_ptr = make();
	std::cout << "How many data points do you want to enter: ";
	int num;
	std::cin >> num;
	fill(*vec_ptr, num);
	display(*vec_ptr);

	return 0;
}