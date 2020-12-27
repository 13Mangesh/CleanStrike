// Header file for CarromBoard class
#pragma once

#include "Player.hpp"

class CarromBoard {
private:
    int blackCoins;
    int redCoins;
    int successiveInvalidInputs;
    Player* currentPlayer;
public:
    CarromBoard();
    void setCurrentPlayer(Player *currentPlayer);
    void strike();
    void multiStrike();
    void redStrike();
    void strikerStrike();
    void defunctCoin();
    void skippedTurn();
    void incrementInvalidInputs();
    void resetInvalidInputs();
    int getBlackcoins();
    int getRedcoins();
    int getInvalidInputCount();
    Player* getCurrentPlayer();
    ~CarromBoard();
};
