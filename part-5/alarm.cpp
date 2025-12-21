#include <iostream>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <windows.h>

#endif

enum class parse_code { SUCCESS, EMPTY_LINE, UNPARSABLE_INPUT, TRAILING_GARBAGE, OUT_OF_RANGE };
parse_code str_to_int(const std::string &line, int &res) noexcept {
    char *end = nullptr;
    errno = 0;
    long value = std::strtol(line.c_str(), &end, 10);

    if(line.empty()){
        return parse_code::EMPTY_LINE;
    } else if(end == line){
        return parse_code::UNPARSABLE_INPUT; // asd
    } else if(*end != '\0'){
        return parse_code::TRAILING_GARBAGE; // 123qwe
    } else if(errno == ERANGE){
        return parse_code::OUT_OF_RANGE; // out of range for long
    } else if(value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()){
        return parse_code::OUT_OF_RANGE; // out of range for int
    } else {
        res = value;
        return parse_code::SUCCESS;
    }
}

void getLog(parse_code code){
    switch(code){
        case parse_code::EMPTY_LINE:
            std::cerr << "empty line!" << std::endl;
            break;
        case parse_code::UNPARSABLE_INPUT:
            std::cerr << "did not recognize even a single digit." << std::endl;
            break;
        case parse_code::TRAILING_GARBAGE:
            std::cerr << "a number followed by nonnumerical character(s)" << std::endl;
            break;
        case parse_code::OUT_OF_RANGE:
            std::cerr << "out of range!" << std::endl;
            break;
        case parse_code::SUCCESS:
            std::cout << "Successfully parsed!" << std::endl;
            break;
    }
}

void handleInput(int &res) {
    std::string line;
    parse_code result_code = parse_code::EMPTY_LINE;
    do {
        if(!std::getline(std::cin, line)){ // ctrl + D / EOF
            std::cerr << "Keyboard interrupt" << std::endl;
            throw std::runtime_error("Input terminated by user");
        }
        if(line == "exit"){ break; }

        result_code = str_to_int(line, res);
        getLog(result_code);
    } while(result_code != parse_code::SUCCESS);
}

int main() {
    int hours = 0, minutes = 0, seconds = 0;

    std::cout << "Hours: ";
    handleInput(hours);
    std::cout << "Minutes: ";
    handleInput(minutes);
    std::cout << "Seconds: ";
    handleInput(seconds);

    int total = seconds + minutes * 60 + hours * 3600;
    using clock = std::chrono::steady_clock;

    auto end = clock::now() + std::chrono::seconds(total);

    while (true) {
        auto now = clock::now();
        if (now >= end) break;

        auto remaining = std::chrono::duration_cast<std::chrono::seconds>(end - now).count();

        std::cout << "\r"
                  << remaining / 3600 << "h\t"
                  << (remaining / 60) % 60 << "m\t"
                  << remaining % 60 << "s\t"
                  << std::flush;

        std::this_thread::sleep_until(now + std::chrono::seconds(1));
    }

    // Sound notification
#ifdef _WIN32
    // I had to take off my headphones for it to work
    // Jingle Bells – Beep version
    Beep(330, 250); // E
    Beep(330, 250); // E
    Beep(330, 500); // E

    Beep(330, 250); // E
    Beep(330, 250); // E
    Beep(330, 500); // E

    Beep(330, 250); // E
    Beep(392, 250); // G
    Beep(262, 250); // C
    Beep(294, 250); // D
    Beep(330, 750); // E

    Beep(349, 250); // F
    Beep(349, 250); // F
    Beep(349, 250); // F
    Beep(349, 250); // F
    Beep(349, 250); // F

    Beep(330, 250); // E
    Beep(330, 250); // E
    Beep(330, 250); // E

    Beep(392, 250); // G
    Beep(392, 250); // G
    Beep(349, 250); // F
    Beep(294, 250); // D
    Beep(262, 750); // C
#else
    // sox is required
    // sudo pacman -S sox
    // 392.0 // G
    // 261.6 // C
    // 293.7 // D
    // 329.6 // E
    // 349.2 // F
    system("play -n synth 0.25 sin 329.6 : synth 0.25 sin 329.6 : synth 0.5 sin 329.6 \
        : synth 0.25 sin 329.6 : synth 0.25 sin 329.6 : synth 0.5 sin 329.6 \
        : synth 0.25 sin 329.6 : synth 0.25 sin 392 : synth 0.25 sin 261.6  \
        : synth 0.25 sin 293.7 : synth 0.95 sin 329.6 : synth 0.25 sin 349.2 \
        : synth 0.25 sin 349.2 : synth 0.25 sin 349.2 : synth 0.25 sin 349.2 \
        : synth 0.25 sin 349.2 : synth 0.25 sin 329.6 : synth 0.25 sin 329.6 \
        : synth 0.25 sin 329.6 : synth 0.25 sin 393 : synth 0.25 sin 393 \
        : synth 0.25 sin 349.2 : synth 0.25 sin 293.7 : synth 0.75 sin 261.6");


#endif
    std::cout << "\nTime is up!\n";
}
