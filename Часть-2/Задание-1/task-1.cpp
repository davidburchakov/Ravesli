#include <cmath>
#include <iostream>
#include <cstdlib>
 
namespace auxiliary {
    void getInput(std::string &line, double &res_double, const std::string &message = "") {
        std::cout << message << std::endl;
        std::getline(std::cin, line);
        char *end = nullptr;
        res_double = strtod(line.c_str(), &end);
        if (end == line.c_str() || *end != '\0' || res_double == HUGE_VAL) {
            std::cerr << "Incorrect input" << std::endl;
        }
    }
} namespace aux = auxiliary;
 
int main(int argc, char* argv[]) {
    std::string distance_str;
    std::string gas_per_100km_str;
    std::string gas_price_str;
 
    double distance_double = -1;
    double gas_per_100km_double = -1;
    double gas_price_double = -1;
 
    aux::getInput(distance_str, distance_double, "Please enter distance: ");
 
    aux::getInput(gas_per_100km_str, gas_per_100km_double,  "Please enter consumption per 100km: ");
 
    aux::getInput(gas_price_str, gas_price_double, "Please enter gas price per liter: ");
 
    std::cout << distance_double << " " << gas_per_100km_double << " " << gas_price_double << std::endl;
    double dacha_trip_cost = (distance_double*gas_per_100km_double*gas_price_double*2)/100;
    std::cout << dacha_trip_cost << std::endl;
}
