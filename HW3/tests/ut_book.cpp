#include <gtest/gtest.h>
#include <string>
#include <memory>
#include "../src/book.h"

TEST(BookTest, ConstructorAndGetters) {
    //Arrange
    auto book = std::make_unique<Book>(1, "Clean Code", "Robert C. Martin");

    //Act & Assert
    EXPECT_EQ(book->get_id(), 1);
    EXPECT_EQ(book->get_title(), "Clean Code");
    EXPECT_EQ(book->get_author(), "Robert C. Martin");
}        

TEST(BookTest, GetBookType) {
    //Arrange
    auto book = std::make_unique<Book>(1, "Clean Code", "Robert C. Martin");

    //Act
    std::string type = book->get_type();

    //Assert
    EXPECT_EQ(type, "Book");
}

TEST(BookTest, GetBookToString) {
    //Arrange
    auto book = std::make_unique<Book>(1, "Clean Code", "Robert C. Martin");

    //Act
    std::string str = book->to_string();

    //Assert
    EXPECT_EQ(str, "Book: Clean Code by Robert C. Martin");
}

TEST(BookTest, ConstructorWithEmptyTitleShouldThrow) {
    EXPECT_THROW(Book(1, "", "Author"), std::invalid_argument);
}

TEST(BookTest, ConstructorWithEmptyAuthorShouldThrow) {
    EXPECT_THROW(Book(1, "Title", ""), std::invalid_argument);
}

TEST(BookTest, ConstructorWithInvalidIdShouldThrow) {
    EXPECT_THROW(Book(0, "Title", "Author"), std::invalid_argument);
}