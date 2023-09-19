// challenge solution for palindrome task
// with use of queue and stack
#include <cctype>
#include <stack>
#include <queue>
#include <iostream>
#include <string>
#include <iomanip>

bool is_palindrome(const std::string& s) {
	std::stack<char> stack;
	std::queue<char> queue;

	// add all the string chars that are alpha to the back of the queue
	// push all the string chars that are alpha on the stack

	for (char c : s) {
		if (std::isalpha(c)) {
			c = std::toupper(c);
			queue.push(c);
			stack.push(c);
		}
	}

	char c1{};
	char c2{};

	while (!queue.empty()) {
		c1 = queue.front();
		queue.pop();
		c2 = stack.top();
		stack.pop();
		if (c1 != c2) {
			return false;
		}
	}
	return true;
}

int main()
{
	std::vector<std::string> test_strings{ "a", "aa", "aba", "abba", "abbcbba", "ab", "abc", "radar", "bob", "ana",
		"avid diva", "Amore, Roma", "A Toyota's a toyota", "A Santa at NASA", "C++",
		"A man, a plan, a cat, a ham, a yak, a yam, a hat, a canal-Panama!", "This is a palindrome", "palindrome" };

	std::cout << std::boolalpha;
	std::cout << std::setw(8) << std::left << "Result" << "String" << std::endl;
	for (const auto& s : test_strings) {
		std::cout << std::setw(8) << std::left << is_palindrome(s) << s << std::endl;
	}
	std::cout << std::endl;
	return 0;
}