#include <iostream>
#include <string>
#include <thread>
#include <chrono>
 
void telegraph_with_cursor(const std::string& message) {
    constexpr auto cursor_on  = std::chrono::milliseconds(100);
    constexpr auto cursor_off = std::chrono::milliseconds(100);
    constexpr int  blink_count = 2;
 
    for (int i = 0; i < 10; ++i) {
        std::cout << "_" << std::flush;
        std::this_thread::sleep_for(cursor_on);
 
        std::cout << "\b \b" << std::flush; // erase cursor
	// std::cout << '\b' << "  " << '\b' << std::flush;

        std::this_thread::sleep_for(cursor_off);
    }
 
    for (const char chr : message) {
        // Blink cursor before character
        for (int i = 0; i < blink_count; ++i) {
            std::cout << "_" << std::flush;
            std::this_thread::sleep_for(cursor_on);
 
            std::cout << "\b \b" << std::flush; // erase cursor
            std::this_thread::sleep_for(cursor_off);
        }
 
        std::cout << chr << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
 
    std::cout << std::endl;
}
 
int main() {
    std::string message = "Hello. Man, how are you holding up there?";
    telegraph_with_cursor(message);
    return 0;
}


