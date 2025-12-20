#include <iostream>

/*
    Задание 3.

    Для меня самое лучшее решение — использовать массив для хранения словаря.
    char — это на самом деле целочисленный тип данных с размером 1byte (8bit).  Поэтому можно использовать char как int.
    char -127+128
    unsigned char 256

    Единственное что такой трюк для кириллицы не подойдёт, ибо кириллица не входит в однобайтовый ascii. Тут нужно думать воркэраунды…
    Код для английского алфавита:
*/
void str_to_morse(const std::string &str) {
    constexpr int ALPHABET_SIZE_ENG = 'z' - 'a' + 1;
    const std::string arr_map[ALPHABET_SIZE_ENG] = {
        ".-",    // a
        "-...",  // b
        "-.-.",  // c
        "-..",   // d
        ".",     // e
        "..-.",  // f
        "--.",   // g
        "....",  // h
        "..",    // i
        ".---",  // j
        "-.-",   // k
        ".-..",  // l
        "--",    // m
        "-.",    // n
        "---",   // o
        ".--.",  // p
        "--.-",  // q
        ".-.",   // r
        "...",   // s
        "-",     // t
        "..-",   // u
        "...-",  // v
        ".--",   // w
        "-..-",  // x
        "-.--",  // y
        "--.."   // z
    };

    for (const char &chr: str) {
        if (chr >= 'a' && chr <= 'z') {
            std::cout << arr_map[chr - 'a'] << " ";
        }
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    std::cout << "Please provide a sentence to convert to morse code" << std::endl;
    std::string line;
    std::getline(std::cin, line);
    str_to_morse(line);
}
