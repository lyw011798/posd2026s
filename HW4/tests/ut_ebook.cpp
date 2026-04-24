#include <gtest/gtest.h>
#include <string>
#include <memory>
#include <stdexcept>
#include "../src/ebook.h"

TEST(EBookTest, ConstructorAndGetters) {
    // Arrange
    auto ebook = std::make_unique<EBook>(3001, "The Pragmatic Programmer", "Hunt");

    // Act & Assert
    EXPECT_EQ(ebook->get_id(), 3001);
    EXPECT_EQ(ebook->get_title(), "The Pragmatic Programmer");
    EXPECT_EQ(ebook->get_author(), "Hunt");
}

TEST(EBookTest, GetType) {
    // Arrange
    auto ebook = std::make_unique<EBook>(3001, "The Pragmatic Programmer", "Hunt");

    // Act
    std::string type = ebook->get_type();

    // Assert
    EXPECT_EQ(type, "EBook");
}

TEST(EBookTest, ToString) {
    // Arrange
    auto ebook = std::make_unique<EBook>(3001, "The Pragmatic Programmer", "Hunt");

    // Act
    std::string str = ebook->to_string();

    // Assert
    EXPECT_EQ(str, "EBook: The Pragmatic Programmer by Hunt");
}

TEST(EBookTest, ConstructorValidation) {
    EXPECT_THROW(EBook(0, "Title", "Author"), std::invalid_argument);
    EXPECT_THROW(EBook(3001, "", "Author"), std::invalid_argument);
    EXPECT_THROW(EBook(3001, "Title", ""), std::invalid_argument);
}
