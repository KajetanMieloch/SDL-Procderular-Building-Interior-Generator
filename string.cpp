#include <iostream>
#include <string>

int main() {
    int number = 42;
    std::string str = std::to_string(number);
    std::cout << "Number as a string: " << str << std::endl;
    return 0;
}
