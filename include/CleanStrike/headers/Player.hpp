// Header file for Player class
#pragma once

class Player
{
private:
    int score;
    int foulCount;
    int noSuccessiveStrikeCount;
public:
    Player();
    void updateScore(int points);
    void resetFoulCount();
    void resetNoSuccessiveStrikeCount();
    void incrementFoulCount();
    void incrementNoSuccessiveStrikeCount();
    int getScore();
    int getFoulCount();
    int getNoSuccessiveStrikeCount();

    ~Player();
};