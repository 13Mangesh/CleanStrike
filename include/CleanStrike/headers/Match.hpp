// Header file for Match class
#pragma once

#include "CarromBoard.hpp"

#include <string>
#include <iostream>
#include <vector>

class Match {
private:
    std::vector<std::string> input;
    int noOfPlayers;
    std::string gameResult;
    bool isGameEndedWithResult;
    std::vector<Player> players;
    Player firstPlayer;
    Player secondPlayer;
    CarromBoard board;
public:
    static int gameNumber;
    Match(std::vector<std::string> input, std::string noOfPlayers);
    void startGame();
    bool isGameFinished();
    void isGameEndedWithoutResult();
    bool getIsGameEndedWithResult();
    int whichPlayerIsWinning(int index);
    std::string getGameResult();
    int changePlayer(int i);
    ~Match();
};