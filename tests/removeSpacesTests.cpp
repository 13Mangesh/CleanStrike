#include <gtest/gtest.h>
#include "../src/utils/removeSpaces.hpp"

TEST(RemoveSpacesTest, correctOutputWithSampleInputTest) {
    // Arrange
    std::string inputLine = "1 2 4   6  1   7  12         2";
    std::vector<std::string> matchInputs;
    std::vector<std::string> expectedMatchInputs = {"1", "2", "4", "6", "1", "7", "12", "2"};

    // Act
    removeSpaces(inputLine, matchInputs);

    // Assert
    ASSERT_EQ(matchInputs, expectedMatchInputs);
}

TEST(RemoveSpacesTest, correctOutputWithNoSpacesInputTest) {
    // Arrange
    std::string inputLine = "122092";
    std::vector<std::string> matchInputs;
    std::vector<std::string> expectedMatchInputs = {"122092"};

    // Act
    removeSpaces(inputLine, matchInputs);

    // Assert
    ASSERT_EQ(matchInputs, expectedMatchInputs);
}

TEST(RemoveSpacesTest, correctOutputWithEmptyInputTest) {
    // Arrange
    std::string inputLine = "";
    std::vector<std::string> matchInputs;
    std::vector<std::string> expectedMatchInputs = {};

    // Act
    removeSpaces(inputLine, matchInputs);

    // Assert
    ASSERT_EQ(matchInputs, expectedMatchInputs);
}