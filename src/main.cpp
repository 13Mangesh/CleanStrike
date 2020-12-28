#include <iostream>
#include <vector>
#define isWindows 0

#ifdef _WIN32
    #define isWindows 1
    #include <windows.h>
#endif

#define RESET   "\033[0m"
#define GREEN   "\033[4m\033[1m\033[32m"
#define WHITE   "\033[1m\033[37m"

#include "../include/CleanStrike/headers/Match.hpp"
#include "utils/removeSpaces.hpp"
#include "utils/takeInput.hpp"

using namespace std;

int main() {
    if(isWindows)
      system("color 07");
    vector<string> inputs;

    takeInputFromFile("./inputs/inputFile.txt", inputs);

    for(string inputLine: inputs) {
        vector<string> matchInputs;
        removeSpaces(inputLine, matchInputs);
        
        Match newMatch = Match(matchInputs);
        newMatch.startGame();
    }

    std::cout<<WHITE<<"\nLog Files are generated in "<<RESET<<GREEN<<"build/logs"<<RESET<<WHITE<<" directory"<<"\n\n\n"<<RESET;
    return 0;
}
