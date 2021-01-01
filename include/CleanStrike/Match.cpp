#include "headers/Match.hpp"
#include <fstream>
#include <string>

// Define color scheme for output
#define RESET   "\033[0m"
#define RED     "\033[1m\033[31m"
#define GREEN   "\033[1m\033[32m"
#define YELLOW  "\033[1m\033[33m"
#define BLUE    "\033[1m\033[34m"
#define MAGENTA "\033[1m\033[35m"
#define CYAN    "\033[1m\033[36m"
#define WHITE   "\033[1m\033[37m"

// Initialize the static variable to keep track of number of games
int Match::gameNumber = 1;

// For testing purposes also initialize the gameResult variable
Match::Match(std::vector<std::string> input, std::string noOfPlayers) {
    this->input = input;
    this->noOfPlayers = stoi(noOfPlayers);
    gameResult = "None";
    isGameEndedWithResult = false;
    // firstPlayer = Player();
    // secondPlayer = Player();
    for(int i = 0; i < this->noOfPlayers; i++) {
        Player newPlayer = Player();
        players.push_back(newPlayer);
    }

}

void printFancyGameNumber() {
    std::cout<<MAGENTA<<"#########################\n"<<RESET;
    std::cout<<MAGENTA<<"#                       #\n"<<RESET;
    std::cout<<MAGENTA<<"#\tGame No: "<<Match::gameNumber++<<"\t#\n"<<RESET;
    std::cout<<MAGENTA<<"#                       #\n"<<RESET;
    std::cout<<MAGENTA<<"#########################\n"<<RESET;
}

int Match::changePlayer(int i) {
    int currentPlayerIndex = (i % noOfPlayers);
    return currentPlayerIndex;
}

void Match::startGame() {
    int flag = 1;

    std::fstream logFile;
    std::string logFilePath = "logs/Log " + std::to_string(Match::gameNumber) + ".txt";
    logFile.open(logFilePath, std::ios::out);
    if (logFile.is_open()) {
        logFile<<"Game no: "<<std::to_string(Match::gameNumber)<<"\n";
    }

    printFancyGameNumber();

    for(int i = 0; i < input.size(); i++) {
        // Change current player logic
        // if (flag & 1) {
        //     flag = 0;
        //     board.setCurrentPlayer(&firstPlayer);
        // } else {
        //     flag = 1;
        //     board.setCurrentPlayer(&secondPlayer);
        // }
        int indexOfCurrentPlayer = changePlayer(i);
        board.setCurrentPlayer(&players[indexOfCurrentPlayer]);

        // Based on input decide what should be done
        if (input[i] == "1") {
            board.strike();
        } else if (input[i] == "2") {
            board.multiStrike();
        } else if (input[i] == "3") {
            board.redStrike();
        } else if (input[i] == "4") {
            board.strikerStrike();
        } else if (input[i] == "5") {
            board.defunctCoin();
        } else if (input[i] == "6") {
            board.skippedTurn();
        } else {
            board.incrementInvalidInputs();
        }

        // Log the stats after each input of both players as well as the board
        if (logFile.is_open()) {
            logFile<<"\nFor Input: "<<input[i]<<"\n";
            std::string currentPlayer = ((i % 2 == 0) ? "Player 1" : "Player 2");
            logFile<<"Current Player is: "<<currentPlayer<<"\n";
            logFile<<"Player 1 - "<<std::to_string(firstPlayer.getScore())<<"\t"<<"Player 2 - "<<std::to_string(secondPlayer.getScore())<<"\n";
            logFile<<"Remaining Black Coins - "<<std::to_string(board.getBlackcoins())<<"\t"<<"Remaining Red Coins - "<<std::to_string(board.getRedcoins())<<"\n";
        }

        // After each input check if one of the game termination condition is met
        if (isGameFinished()) {
            isGameEndedWithResult = true;
            break;
        }
    }

    // If input gets exhausted before any game termination condition is met then output respective warning
    isGameEndedWithoutResult();

    // Close the prevoiusly opened log file
    logFile.close();
}

int Match::whichPlayerIsWinning(int index) {
    for(int i = 0; i < noOfPlayers; i++) {
        if(i == index) continue;
    
        if(players[index].getScore() >= 5 && ((players[index].getScore() - players[i].getScore())) >= 3) {
            return index;
        }
    }
    return -1;
}

bool Match::isGameFinished() {
    int firstPlayerScore = firstPlayer.getScore();
    int secondPlayerScore = secondPlayer.getScore();
    int invalidInputCount = board.getInvalidInputCount();
    int remainingBlackCoins = board.getBlackcoins();
    int remainingRedCoins = board.getRedcoins();

    for(int i = 0; i < noOfPlayers; i++) {
        if(whichPlayerIsWinning(i) != -1) {
            std::cout<<GREEN<<"WINNER:\tPlayer "<<i+1<<"\n"<<RESET;
            std::cout<<BLUE<<"ScoreCard:\n"<<RESET;
            for(int i = 0; i < noOfPlayers; i++) {
                std::cout<<CYAN<<"Player : "<<i+1<<" -"<<players[i].getScore()<<" Points\n"<<RESET;
            }
            // std::cout<<CYAN<<"Player 2: "<<secondPlayerScore<<" Points\n"<<RESET;
            // std::cout<<WHITE<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"<<RESET;
            std::string winningPlayerIndex = std::to_string(i+1);
            gameResult = "Player " + winningPlayerIndex + " Wins";
            return true;
        }
    }

    // if (firstPlayerScore >= 5 && (firstPlayerScore - secondPlayerScore >= 3)) {
    //     std::cout<<GREEN<<"WINNER:\tPlayer 1\n"<<RESET;
    //     std::cout<<BLUE<<"ScoreCard:\n"<<RESET;
    //     std::cout<<CYAN<<"Player 1: "<<firstPlayerScore<<" Points\n"<<RESET;
    //     std::cout<<CYAN<<"Player 2: "<<secondPlayerScore<<" Points\n"<<RESET;
    //     std::cout<<WHITE<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"<<RESET;
    //     gameResult = "FirstPlayerWins";
    //     return true;
    // }

    // if (secondPlayerScore >= 5 && (secondPlayerScore - firstPlayerScore >= 3)) {
    //     std::cout<<GREEN<<"WINNER:\tPlayer 2\n"<<RESET;
    //     std::cout<<BLUE<<"ScoreCard:\n"<<RESET;
    //     std::cout<<CYAN<<"Player 2: "<<secondPlayerScore<<" Points\n"<<RESET;
    //     std::cout<<CYAN<<"Player 1: "<<firstPlayerScore<<" Points\n"<<RESET;
    //     std::cout<<WHITE<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"<<RESET;
    //     gameResult = "SecondPlayerWins";
    //     return true;
    // }

    if((remainingBlackCoins == 0) && (remainingRedCoins == 0)) {
        std::cout<<YELLOW<<"DRAW\n"<<RESET;
        std::cout<<BLUE<<"ScoreCard:\n"<<RESET;
        std::cout<<CYAN<<"Player 1: "<<firstPlayerScore<<" Points\n"<<RESET;
        std::cout<<CYAN<<"Player 2: "<<secondPlayerScore<<" Points\n\n"<<RESET;
        std::cout<<BLUE<<"Coins Remaining on Board:\n"<<RESET;
        std::cout<<CYAN<<"Black Coins:\t"<<remainingBlackCoins<<"\n"<<RESET;
        std::cout<<CYAN<<"Red Coins:\t"<<remainingRedCoins<<"\n"<<RESET;
        std::cout<<WHITE<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"<<RESET;
        gameResult = "GameDraw";
        return true;
    }

    if(invalidInputCount >= 15) {
        std::cout<<RED<<"MATCH STOPPED ABRUPTLY\n"<<RESET;
        std::cout<<YELLOW<<"Too many successive wrong inputs (More than or Equal to 15)\n"<<RESET;
        std::cout<<WHITE<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"<<RESET;
        gameResult = "TooManyInvalidInputs";
        return true;
    }

    return false;
}

void Match::isGameEndedWithoutResult() {
    if(isGameEndedWithResult == false) {
        std::cout<<RED<<"INPUT EXHAUSTED\n"<<RESET;
        std::cout<<YELLOW<<"The match ended without any result\n"<<RESET;
        std::cout<<WHITE<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"<<RESET;
        gameResult = "InputExhausted";
    }
}

bool Match::getIsGameEndedWithResult() {
    return isGameEndedWithResult;
}

std::string Match::getGameResult() {
    return gameResult;
}

Match::~Match() {}
