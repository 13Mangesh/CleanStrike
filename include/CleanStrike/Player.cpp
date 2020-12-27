#include "headers/Player.hpp"

Player::Player() {
    score = 0;
    foulCount = 0;
    noSuccessiveStrikeCount = 0;
}

// If score is getting below 0 by any updation then make score 0 (as minimum score is set to 0)
void Player::updateScore(int points) {
    score = score + points;
    if (score < 0)
        score = 0;
}

void Player::resetFoulCount() {
    foulCount = 0;
}

void Player::resetNoSuccessiveStrikeCount() {
    noSuccessiveStrikeCount = 0;
}

void Player::incrementFoulCount() {
    foulCount++;
    if(foulCount == 3) {
        updateScore(-1);
        resetFoulCount();
    }
}

void Player::incrementNoSuccessiveStrikeCount() {
    noSuccessiveStrikeCount++;
    if (noSuccessiveStrikeCount == 3) {
        updateScore(-1);
        incrementFoulCount();
        resetNoSuccessiveStrikeCount();
    }
}

int Player::getScore() {
    return score;
}

int Player::getFoulCount() {
    return foulCount;
}

int Player::getNoSuccessiveStrikeCount() {
    return noSuccessiveStrikeCount;
}

Player::~Player() {}
