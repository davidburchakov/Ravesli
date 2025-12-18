#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
 
double groceriesCalculator(double total_sum) {
    if (total_sum > 1000) {
        std::cout << "Вам предоставляется скидка в 5%" << std::endl;
        return total_sum * 0.95;
    } else if (total_sum > 500) {
        std::cout << "Вам предоставляется скидка в 3%" << std::endl;
        return total_sum * 0.97;
    } else {
        return total_sum;
    }
}
 
double getInput(std::string &line, const std::string &message = "") {
    std::cout << message << std::endl;
    std::getline(std::cin, line);
    char * end = nullptr;
    double user_input_double = strtod(line.c_str(), &end);
    if (end == line.c_str() || *end != '\0' || user_input_double == HUGE_VAL) {
        std::cerr << "Incorrect input!" << std::endl; // логирование ошибки
    }
    return user_input_double; // вернёт 0 даже если неправильный ввод
}
 
int main(int argc, char* argv[]) {
    std::string message = "Введите сумму покупки: ";
    std::string line;
    double user_input_double = getInput(line, message);
    double total_amount_due = groceriesCalculator(user_input_double);
    std::cout << "Ваш счёт: " << total_amount_due << std::endl;
}


