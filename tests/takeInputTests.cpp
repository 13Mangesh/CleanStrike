#include <gtest/gtest.h>

#include "../src/utils/takeInput.hpp"

TEST(TakeInputFromFileTest, nonExistentFileAsInputTest) {
    // Arrange
    std::string fileName = "fileDoNotExists.txt";
    std::vector<std::string> inputs;
    std::vector<std::string> expectedInputs = {};

    // Act
    takeInputFromFile(fileName, inputs);

    // Assert
    ASSERT_EQ(inputs, expectedInputs);
}

TEST(TakeInputFromFileTest, existentFileAsInputTest) {
    // Arrange
    std::string fileName = "../src/inputs/inputFile.txt";
    std::vector<std::string> inputs;

    // Act
    takeInputFromFile(fileName, inputs);

    // Assert
    ASSERT_GT(inputs.size(), 0);
}

TEST(HasOnlySpacesTest, passingEmptyStringTest) {
    // Arrange
    std::string inputLine = "";

    // Act
    bool result = hasOnlySpaces(inputLine);

    // Assert
    ASSERT_TRUE(result);
}

TEST(HasOnlySpacesTest, passingStringWithOnlySpacesTest) {
    // Arrange
    std::string inputLine = "                      ";

    // Act
    bool result = hasOnlySpaces(inputLine);

    // Assert
    ASSERT_TRUE(result);
}

TEST(HasOnlySpacesTest, passingNonEmptyStringTest) {
    // Arrange
    std::string inputLine = "  1 3 1     5";

    // Act
    bool result = hasOnlySpaces(inputLine);

    // Assert
    ASSERT_FALSE(result);
}