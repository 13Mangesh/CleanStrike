#include <gtest/gtest.h>

#include "../include/CleanStrike/headers/Player.hpp"

// Fixture for Player class

struct PlayerTest: public testing::Test {
    // Arrange
    Player *player;
    
    void SetUp() {
        player = new Player();
    }

    void TearDown() {
        delete player;
    }
};

// Score tests

TEST_F(PlayerTest, initialScoreTest) {
    // Act
    const int initialScore = player->getScore();

    // Assert
    ASSERT_EQ(initialScore, 0);
}

TEST_F(PlayerTest, scoreIncrementTest) {
    // Act
    player->updateScore(1);

    // Assert
    ASSERT_EQ(player->getScore(), 1);
}

TEST_F(PlayerTest, scoreIncrementByTenTest) {
    // Act
    player->updateScore(10);

    // Assert
    ASSERT_EQ(player->getScore(), 10);
}


TEST_F(PlayerTest, scoreNotLessThanZeroTest) {
    // Act
    player->updateScore(-10);

    // Assert
    ASSERT_GE(player->getScore(), 0);
}

// Foul count Tests

TEST_F(PlayerTest, initialFoulCountTest) {
    // Act
    const int initialFoulCount = player->getFoulCount();

    // Assert
    ASSERT_EQ(initialFoulCount, 0);
}

TEST_F(PlayerTest, foulCountIncrementTest) {
    // Act
    player->incrementFoulCount();

    // Assert
    ASSERT_EQ(player->getFoulCount(), 1);
}

TEST_F(PlayerTest, resetFoulCountTest) {
    // Act
    player->resetFoulCount();

    // Assert
    ASSERT_EQ(player->getFoulCount(), 0);

}

// No Successive Strike Count tests

TEST_F(PlayerTest, initialNoSuccessiveStrikeCountTest) {
    // Act
    const int initialNoSuccessiveStrikeCount = player->getNoSuccessiveStrikeCount();

    // Assert
    ASSERT_EQ(initialNoSuccessiveStrikeCount, 0);
}

TEST_F(PlayerTest, noSuccessiveStrikeCountIncrementTest) {
    // Act
    player->incrementNoSuccessiveStrikeCount();

    // Assert
    ASSERT_EQ(player->getNoSuccessiveStrikeCount(), 1);
}

TEST_F(PlayerTest, resetNoSuccessiveStrikeCountTest) {
    // Act
    player->resetNoSuccessiveStrikeCount();

    // Assert
    ASSERT_EQ(player->getNoSuccessiveStrikeCount(), 0);
}

// Score penalty tests

TEST_F(PlayerTest, pointDeductionAfterThreeFoulsTests) {
    // Act
    player->updateScore(5);
    player->incrementFoulCount();
    player->incrementFoulCount();
    player->incrementFoulCount();

    // Assert
    ASSERT_EQ(player->getScore(), 4);
}

TEST_F(PlayerTest, pointDeductionAfterThreeNoStrikesTests) {
    // Act
    player->updateScore(5);
    player->incrementNoSuccessiveStrikeCount();
    player->incrementNoSuccessiveStrikeCount();
    player->incrementNoSuccessiveStrikeCount();

    // Assert
    ASSERT_EQ(player->getScore(), 4);
}

// Reset tests

TEST_F(PlayerTest, foulCountResetAfterPointDeduction) {
    // Act
    player->updateScore(5);
    player->incrementFoulCount();
    player->incrementFoulCount();
    player->incrementFoulCount();

    // Assert
    ASSERT_EQ(player->getFoulCount(), 0);
}

TEST_F(PlayerTest, noSuccessiveStrikeCountResetAfterPointDeduction) {
    // Act
    player->updateScore(5);
    player->incrementNoSuccessiveStrikeCount();
    player->incrementNoSuccessiveStrikeCount();
    player->incrementNoSuccessiveStrikeCount();

    // Assert
    ASSERT_EQ(player->getNoSuccessiveStrikeCount(), 0);
}
