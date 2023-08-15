#include <iostream>
#include <string>

int main() {
    std::string inputString;
    std::cout << "Enter a string: ";
    std::cin >> inputString;

    size_t length = inputString.length();

    for (size_t i{ 0 }; i < length; ++i) {
        // write into output spaces
        for (int j{ 0 }; j < length - 1 - i; ++j) {
            std::cout << " ";
        }

        // write into output left chars
        for (int j{ 0 }; j <= i; ++j) {
            std::cout << inputString[j];
        }

        // write into output right chars
        for (int j = i - 1; j >= 0; --j) {
            std::cout << inputString[j];
        }

        std::cout << std::endl;
    }

    return 0;
}