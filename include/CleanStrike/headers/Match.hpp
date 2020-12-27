// Header file for Match class
#pragma once

#include "CarromBoard.hpp"

#include <string>
#include <iostream>
#include <vector>

class Match {
private:
    std::vector<std::string> input;
    std::string gameResult;
    bool isGameEndedWithResult;
    Player firstPlayer;
    Player secondPlayer;
    CarromBoard board;
public:
    static int gameNumber;
    Match(std::vector<std::string> input);
    void startGame();
    bool isGameFinished();
    void isGameEndedWithoutResult();
    bool getIsGameEndedWithResult();
    std::string getGameResult();
    ~Match();
};