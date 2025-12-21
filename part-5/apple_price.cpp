#include <iostream>

namespace auxiliary {
    enum class parse_result { SUCCESS, EMPTY_INPUT, UNPARSABLE_INPUT, TRAILING_GARBAGE, OUT_OF_RANGE };
    static parse_result str_to_double(const std::string &line, double &res) noexcept {
        char *end = nullptr;
        errno = 0;
        double value = strtod(line.c_str(), &end);
        if (line.empty()) {
            return parse_result::EMPTY_INPUT;
        } else if (end == line.c_str()) {
            return parse_result::UNPARSABLE_INPUT;
        } else if (*end != '\0') {
            return parse_result::TRAILING_GARBAGE;
        } else if (errno == ERANGE) {
            return parse_result::OUT_OF_RANGE;
        } else {
            res = value;
            return parse_result::SUCCESS;
        }
    }

    static void getLog(const parse_result &error_code) {
        switch (error_code) {
            case parse_result::SUCCESS:
                std::fputs("SUCCESS!\n", stdout);
                break;
            case parse_result::EMPTY_INPUT:
                std::fputs("line is empty!\n", stderr);
                break;
            case parse_result::UNPARSABLE_INPUT:
                std::fputs("No characters consumed. Couldn't parse event the first character!\n", stderr);
                break;
            case parse_result::TRAILING_GARBAGE:
                std::fputs("trailing nonnumerical character(s) detected\n", stderr);
                break;
            case parse_result::OUT_OF_RANGE:
                std::fputs("Overflow or underflow for double\n", stderr);
                break;
        }
    }
}namespace aux = auxiliary;

// parameter - apple price per kg
void priceList(double apple_price_kg) {
    double apple_price_gr = apple_price_kg / 10.0;
    std::fprintf(stdout, "Weight\tPrice\n(g)\t($)\n");
    for (int i = 1; i < 11; i++) {
        std::fprintf(stdout, "%d\t", i * 100);
        std::fprintf(stdout, "%.2f\n", apple_price_gr * i);
    }
}

int main(int argc, char *argv[]) {
    std::string line;
    double apple_price = 0.0; // price per kg
    aux::parse_result result_code = aux::parse_result::EMPTY_INPUT;
    do {
        std::cout << "Please provide a price for apples for kg" << std::endl;
        if (!std::getline(std::cin, line)) { // ctrl + D
            std::fputs("unable to get user input\n", stderr);
            break;
        }
        if(line == "exit"){ break; }
        result_code = aux::str_to_double(line, apple_price);
        aux::getLog(result_code);
    } while (result_code != aux::parse_result::SUCCESS);

    priceList(apple_price);
}
