#include <iostream>

int main(int argc, char *argv[]) {
    int sum = 0;
    for (int i = 1; i < argc; i++) {
        try {
            int number = std::stoi(argv[i]);
            if (number < 0) { continue; } // скипаем отрицательные числа
            sum += number;
        } catch (const std::exception &ex) {
            std::fputs(ex.what(), stderr);
            std::fputs("\n", stdout);
        }
    }
    std::cout << "sum: " << sum << std::endl;
}
