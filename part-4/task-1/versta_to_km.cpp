#include <limits>
#include <iostream>
#include <string>

double versta_to_km(double versta) {
    return versta * 1.0668;
}

// will accept input with trailing nonnumerical character(s)
// Will fail ctrl+D on linux 
bool getDouble(double &number) {
    if (!(std::cin >> number)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::fputs("Invalid input!\n", stderr);
        return false;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::fputs("Data is successfully provided: ", stdout);
    std::fprintf(stdout, "%.2f\n", number);
    return true;
}

int main(int argc, char *argv[]) {
    double number;

    while (true) {
        std::cout << "Please enter a decimal number" << std::endl;

        if (!getDouble(number)) { 
            if (std::cin.eof()) { // guard from ctrl+D
                std::cout << "End of input. Exiting.\n";
                break;
            }
        } else {
            break;
        }
    }
}
