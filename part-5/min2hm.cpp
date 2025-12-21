#include <cmath>
#include <iostream>
#include <cstdio>

bool getInput(int &number, int &result){
    while (true) {
        printf("Enter an integer: ");
        result = scanf("%d", &number);

        if (result == 1) {
            // Successful integer input
            printf("You entered: %d\n", number);
            break;
        } else if (result == EOF) { 
            // ctrl + D
            printf("\nNo input detected. Exiting.\n");
            return false;
        } else { // scanf return 1 if doesnt match the %d format
            // Invalid input, clear the input buffer
            printf("Invalid input. Please enter an integer.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                // discard invalid characters
            }
        }
    }
    return true;
}

void min2hm(int minutes){
    double time = static_cast<double>(minutes) / 60.0; 
    int hours = std::floor(time); 
    double minutes_res = minutes % 60;
    std::cout << minutes << " minutes = " << hours 
    << " hours " << minutes_res << " minutes" << std::endl;
}

int main(int argc, char *argv[]) {
    int number;
    int result;
    if(getInput(number, result)){
        min2hm(number);
    }
    return 0;
}
