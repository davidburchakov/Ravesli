#include <limits>
#include <iostream>
#include <sstream>
#include <string>

bool read_double(double& value) {
    std::string line;
    if (!std::getline(std::cin, line)) {
        return false; // EOF or ctrl+D
    }
    std::stringstream ss(line);
    if (!(ss >> value)) { // failed to convert, probably nonnumerical chars or empty
        std::cerr << "Invalid number\n";
        return false;
    }
    // Check for trailing garbage
    char leftover;
    if (ss >> leftover) {
        std::cerr << "Trailing characters detected\n";
        return false;
    }
    return true;
}

/*
 * I perform all the calculations in a single function,
 * so there's no need to traverse through the whole array multiple times
*/
void perform_calculations(const double nums[], const int &n, double &mean, double &min_val, double &max_val) {
    for (int i = 0; i < n; i++) {
        min_val = std::min(nums[i], min_val);
        max_val = std::max(nums[i], max_val);
        mean += nums[i];
    }
    mean = mean / n;
}

int main() {
    constexpr int n = 5;
    double nums[n];
    std::cout << "Please, provide " << n << " decimal numbers" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Enter a decimal number: \n";
        while (!read_double(nums[i])) {
            std::cout << "Invalid input. Exiting.\n";
            break; //  need this to handle ctrl+D
        }
        std::cout << "You entered: " << nums[i] << '\n';
    }

    std::cout << "You provided the following decimal numbers: ";
    for (unsigned int i = 0; i < n; i++) {
        std::fprintf(stdout, "%.2f ", nums[i]);
    }
    std::cout << std::endl;

    double mean = 0;
    double min_val = std::numeric_limits<double>::max();
    double max_val = std::numeric_limits<double>::min();
    perform_calculations(nums, n, mean, min_val, max_val);
    std::fprintf(stdout, "mean: %.2f\n", mean);
    std::fprintf(stdout, "smallest number: %.2f\n", min_val);
    std::fprintf(stdout, "biggest number: %.2f\n", max_val);
}
