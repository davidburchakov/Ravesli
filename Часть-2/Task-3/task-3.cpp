#include <iostream>
#include <string>
#include <random>
#include <cstdlib>
 
class User {
    std::string name;
    int lvl;
public:
    int& getLvl() { return lvl; }
    std::string getName() const { return name; }
    User(std::string name = "player", int lvl = 1): name(name), lvl(lvl) { }
    friend std::ostream& operator<<(std::ostream &out, const User &usr) {
        out << "username: " << usr.name << "\ncurrent level: " << usr.lvl;
        return out;
    }
};
 
class IRandomGenerator {
public:
    virtual ~IRandomGenerator() = default;
    virtual int generate(int min, int max) = 0;
};
 
class RandomNumberGenerator: public IRandomGenerator {
    std::mt19937 gen;
public:
    RandomNumberGenerator(): gen(std::random_device{}()) { }
    int generate(int min, int max) override {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(gen);
    }
};
 
 
class Game {
    RandomNumberGenerator &rng;
    User &player;
 
    static int convert_str_to_int(const std::string &str) {
        char *end = nullptr;
        int res = strtol(str.c_str(), &end, 10);
        if (end == str.c_str() || *end != '\0') {
            throw std::invalid_argument("Invalid argument provided!");
        }
        return res;
    }
 
    int play() {
        int min_number = 0;
        int max_number = (pow(10, player.getLvl())) - 1; // would overflow at 10^10
        int rand_number = rng.generate(min_number, max_number);
        std::string rand_number_str = std::to_string(rand_number);
        std::string user_input_str;
        int user_input_int = -1;
        while (user_input_int != rand_number) {
            std::cout << "Take a guess!" << std::endl;
 
            if (!std::getline(std::cin, user_input_str)) {
                std::cerr << "Input stream error EOF\n";
            }
            if (user_input_str == "exit") { return 1; }
 
            try {
                user_input_int = convert_str_to_int(user_input_str);
            } catch (const std::exception &ex) {
                std::cerr << "unable to parse str to int: " << ex.what() << std::endl;
                continue;
            }
 
            if (user_input_str.empty() || user_input_str.size() > player.getLvl()) {
                std::cerr << "Expected input is " << min_number << "-" << max_number << std::endl;
                continue;
            }
            size_t n = rand_number_str.size();
            size_t m = user_input_str.size();
            int guessed_counter = 0;
            for (int i = 0; i < std::min(n, m); i++) {
                if (rand_number_str[i] == user_input_str[i]) {
                    guessed_counter++;
                }
            }
            std::cout << "secret number: " << rand_number_str << std::endl;
            std::cout << "Guessed: " << guessed_counter << std::endl;
            if (guessed_counter == n) {
                std::cout << "Congrats! You got the number right! " << rand_number_str << std::endl;
                return 0;
            }
        }
    }
 
public:
    // dependency injection
    Game(User &player, RandomNumberGenerator &rng): player(player), rng(rng) { }
 
    void start() {
        std::cout << player.getName() << " has started the game" << std::endl;
        int gameStatus = -1;
        while (gameStatus != 1) {
            std::cout << "Your current lvl: " << player.getLvl() << std::endl;
            gameStatus = play();
            if (gameStatus == 0) {
                player.getLvl()++;
            }
            if (player.getLvl() > 9) {
                // The game must end at lvl 9, bc pow(10, 10) would overflow integer
                std::cout << "Congrats! " << player.getName() << " has won the game at lvl " << player.getLvl() << "!" << std::endl;
                break;
            }
        }
        std::cout << "The " << player.getName() << " has finished the game" << std::endl;
    }
};
 
int main(int argc, char* argv[]) {
    User usr;
    RandomNumberGenerator rng;
    Game game(usr, rng);
    game.start(); // type "exit" to end
}


