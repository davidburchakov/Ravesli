#include <climits>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cerrno>

/*
    Задание 1. Ну кто тебе сказал, кто придумал что задание 1 — простое? :)

    Тема парсинга сама по себе сложная, существует множество способов заимплементировать парсинг, 
    в зависимости от версии C++, стиля программирования и конкретных нужд.
    scanf, atoi, stoi, streamstring, from_chars, strtol. 
    А представь ещё если нужно во время runtime’а определить систему счисления введённого числа :)
    Я заимплементировал свою функцию таким образом, что она гарантирует принятие только 
    адекватного ввода пользователя и исключает исключения :)
    Сделал, что называется, функцию deterministic. 
    Потому что парсинг — не то место, где я хочу чтобы моя программа поломалась и выключилась.
    
    Критика приветствуется :)

*/

 
namespace parsing {
    bool str_to_double98(const std::string &line, double &res) noexcept {
        char *end = nullptr;
        errno = 0;
        const double value = std::strtod(line.c_str(), &end);
        if (line.empty()) {
            std::fputs("line is empty!\n", stderr);
        } else if (end == line) {
            std::fputs("No characters consumed. Did not recognize even "
                       "a single valid digit at the start of the string\n", stderr);
        } else if (*end != '\0') {
            std::fputs( "numeric result followed by trailing nonnumeric character(s)\n", stderr);
        } else if (errno == ERANGE) {
            std::fputs("Overflow or underflow for double\n", stderr);
        } else {
            // everything's alright
            res = value;
            return true;
        }
        return false;
    }
 
    bool str_to_int98(const std::string &line, int &res) noexcept {
        char *end = nullptr;
        errno = 0;
        const long value = std::strtol(line.c_str(), &end, 10);
        if (line.empty()) {
            std::fprintf(stderr, "line is empty!\n");
        } else if (end == line.c_str()) {
            std::fprintf(stderr, "did not recognize even a single valid digit at the start of the string.\n");
        } else if (*end != '\0') {
            std::fprintf(stderr, "numeric result followed by trailing nonnumeric character(s)\n");
        } else if (errno == ERANGE) {
            std::fprintf(stderr, "Overflow or underflow for long\n");
        } else if (value < INT_MIN || value > INT_MAX) {
            std::fprintf(stderr, "Out of range for int\n");
        } else {
            // everything's alright
            res = static_cast<int>(value);
            return true;
        }
        return false;
    }
} namespace prs = parsing;
 
 
 
/*
 * calculates speed in km per hour
 * takes distance in meters
 * takes time in minutes.seconds
*/
double calc_velocity(int meters, double time) {
    int minutes = static_cast<int>(time);
    double seconds = (time - minutes) * 100;
    double total_seconds = seconds / 60;
    double total_minutes = static_cast<double>(minutes) + total_seconds;
    double hours = total_minutes / 60;
    double kms = static_cast<double>(meters) / 1000;
 
    return kms / hours;
}
 
int main(int argc, char* argv[]) {
    std::string line;
    int meters = -1;
    do{
        std::cout << "Please enter distance in meters, a whole number: " << std::endl;
        std::getline(std::cin, line);
    } while (line != "exit" && !parsing::str_to_int98(line, meters));
    std::cout << "you entered: " << meters << "km per hour" << std::endl;
 
    double minutes = -1;
    do {
        std::cout << "Please enter time in minutes, a decimal number: " << std::endl;
        std::getline(std::cin, line);
    } while (line != "exit" && !prs::str_to_double98(line, minutes));
    std::cout << "You entered: " << minutes << std::endl;
    double velocity = calc_velocity(meters, minutes);
    std::fprintf(stdout, "Your velocity: %.2f km/h\n", velocity);
}
