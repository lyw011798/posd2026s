#include <gtest/gtest.h>
#include <string>
#include <memory>
#include <vector>
#include "../src/book_bundle.h"
#include "../src/book.h"
#include "../src/ebook.h"

TEST(BookBundleTest, Constructor) {
    //Arrange
    auto bundle = std::make_unique<BookBundle>(100, "Mono Bundle");

    //Act & Assert
    EXPECT_EQ(bundle->get_id(), 100);
    EXPECT_EQ(bundle->get_title(), "Mono Bundle");
    EXPECT_EQ(bundle->get_author(), "Multiple Authors");
    EXPECT_EQ(bundle->get_type(), "BookBundle");
}

TEST(BookBundleTest, AddItemToNonNestedBundle) {
    //Arrange
    auto bundle = std::make_unique<BookBundle>(100, "Non-Nested Bundle");
    auto book = std::make_unique<Book>(1, "Book 1", "Author 1");
    auto ebook = std::make_unique<EBook>(2, "EBook 1", "Author 2");

    //Act
    bundle->add_item(book.get());
    bundle->add_item(ebook.get());

    //Assert
    EXPECT_EQ(bundle->get_items(), (std::vector<LibraryItem*>{book.get(), ebook.get()}));
    EXPECT_EQ(bundle->get_author(), "Multiple Authors");
}

TEST(BookBundleTest, AddItemToNestedBundle) {
    //Arrange
    auto parent_bundle = std::make_unique<BookBundle>(100, "Parent Bundle");
    auto bundle = std::make_unique<BookBundle>(101, "Nested Bundle");
    auto book = std::make_unique<Book>(2, "Book 1", "Author 1");
    auto ebook = std::make_unique<EBook>(3, "EBook 1", "Author 2");

    //Act
    bundle->add_item(book.get());
    bundle->add_item(ebook.get());
    parent_bundle->add_item(bundle.get());
      

    //Assert
    EXPECT_EQ(parent_bundle->get_items(), (std::vector<LibraryItem*>{bundle.get()}));
    EXPECT_EQ(parent_bundle->get_author(), "Multiple Authors");
}

TEST(BookBundleTest, NonNestedBundleToString) {
    //Arrange
    auto bundle = std::make_unique<BookBundle>(100, "Non-Nested Bundle");
    auto book = std::make_unique<Book>(1, "Book 1", "Author 1");
    auto ebook = std::make_unique<EBook>(2, "EBook 1", "Author 2");

    //Act
    bundle->add_item(book.get());
    bundle->add_item(ebook.get());
    std::string output = bundle->to_string();
    std::string expected_str = "Bundle: Non-Nested Bundle (items: 2)\n"
      "  Book: Book 1 by Author 1\n"
      "  EBook: EBook 1 by Author 2";
     
    //Assert
    EXPECT_EQ(bundle->to_string(), expected_str);
}

TEST(BookBundleTest, NestedBundleToString) {
    //Arrange
    auto parent_bundle = std::make_unique<BookBundle>(100, "Parent Bundle");
    auto bundle = std::make_unique<BookBundle>(101, "Nested Bundle");
    auto book = std::make_unique<Book>(2, "Book 1", "Author 1");
    auto ebook = std::make_unique<EBook>(3, "EBook 1", "Author 2");

    //Act
    bundle->add_item(book.get());
    bundle->add_item(ebook.get());
    parent_bundle->add_item(bundle.get());
    std::string expected_str = "Bundle: Parent Bundle (items: 1)\n"
      "  Bundle: Nested Bundle (items: 2)\n"
      "    Book: Book 1 by Author 1\n"
      "    EBook: EBook 1 by Author 2";
      

    //Assert
    EXPECT_EQ(parent_bundle->to_string(), expected_str);
    EXPECT_EQ(parent_bundle->get_author(), "Multiple Authors");
}
    
    
    
    