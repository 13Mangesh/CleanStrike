#include <gtest/gtest.h>
#include <vector>
#include <string>

#include "../include/CleanStrike/headers/Match.hpp"

// Create a Fixture for Match class
struct MatchTest: public testing::Test {
    // Arrange
    Match *match;
    std::vector<std::string> input = {"1", "1", "1", "1", "2", "2", "3"};

    void SetUp() {
        match = new Match(input);
    }

    void TearDown() {
        delete match;
    }
};

// Initial tests

TEST_F(MatchTest, initialGameResultTest) {
    // Act
    std::string initialGameResult = match->getGameResult();

    // Assert
    ASSERT_STREQ(initialGameResult.c_str(), "None");
}

TEST_F(MatchTest, initialIsGameEndedWithResultTest) {
    // Act
    bool initialIsGameEndedWithResult = match->getIsGameEndedWithResult();

    // Assert
    ASSERT_FALSE(initialIsGameEndedWithResult);
}

// Tests based on different game terminating conditions

TEST(MatchWithCustomInputTest, isInputHasExhausted) {
    // Arrange
    Match match = Match({"1", "1"});

    // Apply
    match.startGame();

    // Assert
    ASSERT_STREQ(match.getGameResult().c_str(), "InputExhausted");
}

TEST(MatchWithCustomInputTest, firstPlayerWinsTest) {
    // Arrange
    Match match = Match({"1", "1", "3", "6", "2", "6", "2"});

    // Apply
    match.startGame();

    // Assert
    ASSERT_STREQ(match.getGameResult().c_str(), "FirstPlayerWins");
}

TEST(MatchWithCustomInputTest, secondPlayerWinsTest) {
    // Arrange
    Match match = Match({"1", "3", "6", "2", "6", "1", "3"});

    // Apply
    match.startGame();

    // Assert
    ASSERT_STREQ(match.getGameResult().c_str(), "SecondPlayerWins");
}

TEST(MatchWithCustomInputTest, gameDrawTest) {
    // Arrange
    Match match = Match({"3", "2", "6", "1", "2", "2", "1", "2", "1"});

    // Apply
    match.startGame();

    // Assert
    ASSERT_STREQ(match.getGameResult().c_str(), "GameDraw");
}

TEST(MatchWithCustomInputTest, tooManyInvalidInputsTest) {
    // Arrange
    Match match = Match({
        "7", "8", "a", "b", "#", "100", "402", "abc", "A",
        "2323", "@34", "o04#", "312", "111", "2323323", "232",
        "1#E", "3AJK", "MP"
    });

    // Apply
    match.startGame();

    // Assert
    ASSERT_STREQ(match.getGameResult().c_str(), "TooManyInvalidInputs");
}




