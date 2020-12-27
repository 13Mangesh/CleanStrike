#include "headers/CarromBoard.hpp"
#include "headers/Player.hpp"

CarromBoard::CarromBoard() {
    blackCoins = 7;
    redCoins = 1;
    successiveInvalidInputs = 0;
}

// While a match is going on, only one player will be associated with the carrom board
// So for each set a currentPlayer pointer pointing to that particular player
void CarromBoard::setCurrentPlayer(Player *currentPlayer) {
    this->currentPlayer = currentPlayer;
}

void CarromBoard::strike() {
    if (blackCoins <= 0) {
        currentPlayer->incrementNoSuccessiveStrikeCount();
        return;
    }
    blackCoins = blackCoins - 1;
    currentPlayer->updateScore(1);
    currentPlayer->resetNoSuccessiveStrikeCount();
    resetInvalidInputs();
}

void CarromBoard::multiStrike() {
    if (blackCoins < 2) {
        currentPlayer->incrementNoSuccessiveStrikeCount();
        return;
    }
    blackCoins = blackCoins - 2;
    currentPlayer->updateScore(2);
    currentPlayer->resetNoSuccessiveStrikeCount();
    resetInvalidInputs();
}

void CarromBoard::redStrike() {
    if (redCoins <= 0) {
        currentPlayer->incrementNoSuccessiveStrikeCount();
        return;
    }
    redCoins = 0;
    currentPlayer->updateScore(3);
    currentPlayer->resetNoSuccessiveStrikeCount();
    resetInvalidInputs();
}

void CarromBoard::strikerStrike() {
    currentPlayer->updateScore(-1);
    currentPlayer->incrementFoulCount();
    currentPlayer->incrementNoSuccessiveStrikeCount();
    resetInvalidInputs();
}

void CarromBoard::defunctCoin() {
    if (blackCoins <= 0) {
        currentPlayer->incrementNoSuccessiveStrikeCount();
        return;
    }
    blackCoins = blackCoins - 1;
    currentPlayer->updateScore(-2);
    currentPlayer->incrementFoulCount();
    currentPlayer->incrementNoSuccessiveStrikeCount();
    resetInvalidInputs();
}

void CarromBoard::skippedTurn() {
    currentPlayer->incrementNoSuccessiveStrikeCount();
    resetInvalidInputs();
}

// Also it will increment the no successive strike count
void CarromBoard::incrementInvalidInputs() {
    successiveInvalidInputs++;
    currentPlayer->incrementNoSuccessiveStrikeCount();
}

void CarromBoard::resetInvalidInputs() {
    successiveInvalidInputs = 0;
}


int CarromBoard::getBlackcoins() {
    return blackCoins;
}

int CarromBoard::getRedcoins() {
    return redCoins;
}

int CarromBoard::getInvalidInputCount() {
    return successiveInvalidInputs;
}

Player* CarromBoard::getCurrentPlayer() {
    return currentPlayer;
}

CarromBoard::~CarromBoard() {}
