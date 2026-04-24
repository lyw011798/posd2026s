#include <gtest/gtest.h>
#include <string>
#include <memory>
#include <stdexcept>
#include "../src/reference_book.h"

TEST(ReferenceBookTest, ConstructorAndGetters) {
    // Arrange
    auto rb = std::make_unique<ReferenceBook>(2001, "Design Patterns", "GoF");

    // Act & Assert
    EXPECT_EQ(rb->get_id(), 2001);
    EXPECT_EQ(rb->get_title(), "Design Patterns");
    EXPECT_EQ(rb->get_author(), "GoF");
}

TEST(ReferenceBookTest, GetType) {
    // Arrange
    auto rb = std::make_unique<ReferenceBook>(2001, "Design Patterns", "GoF");

    // Act
    std::string type = rb->get_type();

    // Assert
    EXPECT_EQ(type, "ReferenceBook");
}

TEST(ReferenceBookTest, ToString) {
    // Arrange
    auto rb = std::make_unique<ReferenceBook>(2001, "Design Patterns", "GoF");

    // Act
    std::string str = rb->to_string();

    // Assert
    EXPECT_EQ(str, "ReferenceBook: Design Patterns by GoF");
}

TEST(ReferenceBookTest, ConstructorValidation) {
    EXPECT_THROW(ReferenceBook(0, "Title", "Author"), std::invalid_argument);
    EXPECT_THROW(ReferenceBook(2001, "", "Author"), std::invalid_argument);
    EXPECT_THROW(ReferenceBook(2001, "Title", ""), std::invalid_argument);
}
