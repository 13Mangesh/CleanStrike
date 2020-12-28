/*  ****************************************************
    * Creating a Fixture for Carrom Board - Line No 16 *
    * Initial Values test - Line No 32                 *
    * Strike Tests -    Line No 58                     *
    * MultiStrike Tests -   Line No 108                *
    * Red Strike tests -    Line No 148                *
    * Striker Stike tests - Line No 187                *
    * Defunct Coin Tests -  Line No 216                *
    * Skipped Turn Tests -  Line No 263                *
    * Invalid Input Tests - Line No 273                *
    ****************************************************   */
#include <gtest/gtest.h>
#include "../include/CleanStrike/headers/CarromBoard.hpp"
#include "../include/CleanStrike/headers/Player.hpp"

// Creating a Fixture for CarromBoard
struct CarromBoardTest: public testing::Test {
    // Arrange
    CarromBoard *board;
    Player currentPlayer = Player();

    void SetUp() {
        board = new CarromBoard();
        board->setCurrentPlayer(&currentPlayer);
    }

    void TearDown() {
        delete board;
    }
};

// Initial values Tests

TEST_F(CarromBoardTest, initialBlackCointTest) {
    // Act
    const int initialBlackCoins = board->getBlackcoins();

    // Assert
    ASSERT_EQ(initialBlackCoins, 9);
}

TEST_F(CarromBoardTest, initialRedCointTest) {
    // Act
    const int initialRedCoins = board->getRedcoins();

    // Assert
    ASSERT_EQ(initialRedCoins, 1);
}

TEST_F(CarromBoardTest, initialSuccessiveInvalidInputsTest) {
    // Act
    const int initialInvalidInputs = board->getInvalidInputCount();

    // Assert
    ASSERT_EQ(initialInvalidInputs, 0);
}

// Strike Tests

TEST_F(CarromBoardTest, decrementBlackcoinAfterStrikeTest) {
    // Act
    board->strike();
    
    // Assert
    ASSERT_EQ(board->getBlackcoins(), 8);
}

TEST_F(CarromBoardTest, blackCoinsNotLessThanZeroTest) {
    // Act
    for (int i = 0; i < 10; i++) {
        board->strike();    
    }
    
    // Assert
    ASSERT_GE(board->getBlackcoins(), 0);
}

TEST_F(CarromBoardTest, updatePlayerScoreByOneAfterStrikeTest) {
    // Act
    board->strike();

    // Assert
    ASSERT_EQ(board->getCurrentPlayer()->getScore(), 1);
}

TEST_F(CarromBoardTest, resetNoSuccessiveStrikeCountAfterStrikeTest) {
    // Act
    for(int i = 0; i < 5; i++) {
        board->skippedTurn();
    }
    board->strike();

    // Assert
    ASSERT_EQ(board->getCurrentPlayer()->getNoSuccessiveStrikeCount(), 0);
}

TEST_F(CarromBoardTest, resetInvalidInputCountAfterStrikeTest) {
    // Act
    for(int i = 0; i < 5; i++) {
        board->incrementInvalidInputs();
    }
    board->strike();

    // Assert
    ASSERT_EQ(board->getInvalidInputCount(), 0);
}

// MultiStrike Tests

TEST_F(CarromBoardTest, decrementBlackcoinAfterMultistrikeTest) {
    // Act
    board->multiStrike();

    // Assert
    ASSERT_EQ(board->getBlackcoins(), 7);
}


TEST_F(CarromBoardTest, blackCoinsNotLessThanZeroAfterMultistrikeTest) {
    // Act
    for (int i = 0; i < 5; i++) {
        board->multiStrike();    
    }
    
    // Assert
    ASSERT_GE(board->getBlackcoins(), 0);
}

TEST_F(CarromBoardTest, updatePlayerScoreByTwoAfterMultistrikeTest) {
    // Act
    board->multiStrike();

    // Assert
    ASSERT_EQ(board->getCurrentPlayer()->getScore(), 2);
}

TEST_F(CarromBoardTest, resetNoSuccessiveStrikeCountAfteMultistrikeTest) {
    // Act
    for(int i = 0; i < 5; i++) {
        board->skippedTurn();
    }
    board->multiStrike();

    // Assert
    ASSERT_EQ(board->getCurrentPlayer()->getNoSuccessiveStrikeCount(), 0);
}

// Red Strike tests

TEST_F(CarromBoardTest, decrementRedcoinAfterRedstrikeTest) {
    // Act
    board->redStrike();

    // Assert
    ASSERT_EQ(board->getRedcoins(), 0);
}

TEST_F(CarromBoardTest, redCoinsNotLessThanZeroAfterRedstrikeTest) {
    // Act
    for (int i = 0; i < 5; i++) {
        board->redStrike();    
    }
    
    // Assert
    ASSERT_EQ(board->getRedcoins(), 0);
}

TEST_F(CarromBoardTest, updatePlayerScoreByThreeAfterRedstrikeTest) {
    // Act
    board->redStrike();

    // Assert
    ASSERT_EQ(board->getCurrentPlayer()->getScore(), 3);
}

TEST_F(CarromBoardTest, resetNoSuccessiveStrikeCountAfteRedstrikeTest) {
    // Act
    for(int i = 0; i < 5; i++) {
        board->skippedTurn();
    }
    board->redStrike();

    // Assert
    ASSERT_EQ(board->getCurrentPlayer()->getNoSuccessiveStrikeCount(), 0);
}

// Striker Stike tests

TEST_F(CarromBoardTest, decrementPlayerScoreByOneAfterStrikerstrikeTest) {
    // Act
    for(int i = 0; i < 4; i++) {
        board->strike();
    }
    board->strikerStrike();

    // Assert
    ASSERT_EQ(board->getCurrentPlayer()->getScore(), 3);
}

TEST_F(CarromBoardTest, incrementFoulCountAfterStrikerstrikeTest) {
    // Act
    board->strikerStrike();

    // Assert
    ASSERT_EQ(board->getCurrentPlayer()->getFoulCount(), 1);
}

TEST_F(CarromBoardTest, incrementNoSuccessiveStrikeCountAfteStrikerstrikeTest) {
    // Act
    board->strikerStrike();

    // Assert
    ASSERT_EQ(board->getCurrentPlayer()->getNoSuccessiveStrikeCount(), 1);
}

// Defunct Coin Tests

TEST_F(CarromBoardTest, decrementBlackcoinAfterDefunctCoinTest) {
    // Act
    board->defunctCoin();

    // Assert
    ASSERT_EQ(board->getBlackcoins(), 8);
}

TEST_F(CarromBoardTest, blackCoinsNotLessThanZeroAfterDefunctCoinTest) {
    // Act
    for (int i = 0; i < 10; i++) {
        board->defunctCoin();    
    }
    
    // Assert
    ASSERT_EQ(board->getBlackcoins(), 0);
}

TEST_F(CarromBoardTest, decrementPlayerScoreByTwoAfterDefunctCoinTest) {
    // Act
    for(int i = 0; i < 4; i++) {
        board->strike();
    }
    board->defunctCoin();

    // Assert
    ASSERT_EQ(board->getCurrentPlayer()->getScore(), 2);
}

TEST_F(CarromBoardTest, incrementFoulCountAfterDefunctCoinTest) {
    // Act
    board->defunctCoin();

    // Assert
    ASSERT_EQ(board->getCurrentPlayer()->getFoulCount(), 1);
}

TEST_F(CarromBoardTest, incrementNoSuccessiveStrikeCountAfteDefunctCoinTest) {
    // Act
    board->defunctCoin();

    // Assert
    ASSERT_EQ(board->getCurrentPlayer()->getNoSuccessiveStrikeCount(), 1);
}

// Skipped Turn Tests

TEST_F(CarromBoardTest, incrementNoSuccessiveStrikeCountAfteSkippedTurnTest) {
    // Act
    board->skippedTurn();

    // Assert
    ASSERT_EQ(board->getCurrentPlayer()->getNoSuccessiveStrikeCount(), 1);
}

// Invalid Input Tests


TEST_F(CarromBoardTest, invalidInputsIncrementTest) {
    // Act
    board->incrementInvalidInputs();
    // Assert
    ASSERT_EQ(board->getInvalidInputCount(), 1);
}

TEST_F(CarromBoardTest, resetInvalidInputsTest) {
    // Act
    board->resetInvalidInputs();

    // Assert
    ASSERT_EQ(board->getInvalidInputCount(), 0);
}

TEST_F(CarromBoardTest, resetInvalidInputsAfterStrikeTest) {
    // Act
    for(int i = 0; i < 5; i++) {
        board->incrementInvalidInputs();
    }
    board->strike();

    // Assert
    ASSERT_EQ(board->getInvalidInputCount(), 0);
}

TEST_F(CarromBoardTest, resetInvalidInputsAfterMultistrikeTest) {
    // Act
    for(int i = 0; i < 5; i++) {
        board->incrementInvalidInputs();
    }
    board->multiStrike();

    // Assert
    ASSERT_EQ(board->getInvalidInputCount(), 0);
}

TEST_F(CarromBoardTest, resetInvalidInputsAfterRedstrikeTest) {
    // Act
    for(int i = 0; i < 5; i++) {
        board->incrementInvalidInputs();
    }
    board->redStrike();

    // Assert
    ASSERT_EQ(board->getInvalidInputCount(), 0);
}

TEST_F(CarromBoardTest, resetInvalidInputsAfterStrikerStrikeTest) {
    // Act
    for(int i = 0; i < 5; i++) {
        board->incrementInvalidInputs();
    }
    board->strikerStrike();

    // Assert
    ASSERT_EQ(board->getInvalidInputCount(), 0);
}

TEST_F(CarromBoardTest, resetInvalidInputsAfterDefunctCoinTest) {
    // Act
    for(int i = 0; i < 5; i++) {
        board->incrementInvalidInputs();
    }
    board->defunctCoin();

    // Assert
    ASSERT_EQ(board->getInvalidInputCount(), 0);
}

TEST_F(CarromBoardTest, resetInvalidInputsAfterSkippedTurnTest) {
    // Act
    for(int i = 0; i < 5; i++) {
        board->incrementInvalidInputs();
    }
    board->skippedTurn();

    // Assert
    ASSERT_EQ(board->getInvalidInputCount(), 0);
}

TEST_F(CarromBoardTest, incrementNoSuccessiveStrikeCountAfteInvalidInputTest) {
    // Act
    board->incrementInvalidInputs();

    // Assert
    ASSERT_EQ(board->getCurrentPlayer()->getNoSuccessiveStrikeCount(), 1);
}