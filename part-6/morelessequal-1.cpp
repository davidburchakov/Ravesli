#include <limits>
#include <iostream>
 
int getInt() {
    int value = 0;
    if (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        throw std::runtime_error("Incorrect input!");
    }
    std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    std::cout << "successfully parsed!" << std::endl;
    return value;
}
 
void compare(const int &a, const int &b) {
    if (a == b) {
        std::cout << a << " equals " << b << std::endl;
    } else if (a < b) {
        std::cout << a << " is less than " << b << std::endl;
    } else if (b < a) {
        std::cout << b << " is less than " << a << std::endl;
    }
}
 
int main(int argc, char *argv[]) {
    std::cout << "enter a whole number a: " << std::endl;
    int a = getInt();
    std::cout << "enter a whole number b: " << std::endl;
    int b = getInt();
    compare(a, b);
}


