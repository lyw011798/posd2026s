#include <gtest/gtest.h>
#include <memory>
#include "../src/book.h"
#include "../src/ebook.h"
#include "../src/book_bundle.h"
#include "../src/null_iterator.h"
#include "../src/book_bundle_iterator.h"

class IteratorTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(IteratorTest, BookCreateIteratorReturnsNullIterator) {
    // Arrange
    Book book(1, "Effective C++", "Scott Meyers");

    // Act
    Iterator* it = book.create_iterator();
    
    // Assert
    EXPECT_NE(dynamic_cast<NullIterator*>(it), nullptr);
    delete it;
}

TEST_F(IteratorTest, BookBundleCreateIteratorReturnsBookBundleIterator) {
    // Arrange
    BookBundle bundle(2, "C++ Series");

    // Act
    Iterator* it = bundle.create_iterator();
    
    // Assert
    EXPECT_NE(dynamic_cast<BookBundleIterator*>(it), nullptr);
    delete it;
}

TEST_F(IteratorTest, NullIteratorIsDoneReturnsTrue) {
    // Arrange
    NullIterator null_iterator;
    // Act
    bool is_done = null_iterator.is_done();
    // Assert
    EXPECT_TRUE(is_done);
}

TEST_F(IteratorTest, NullIteratorNextThrowsException) {
    // Arrange
    NullIterator null_iterator;
    // Act & Assert
    EXPECT_THROW(null_iterator.next(), std::runtime_error);
}

TEST_F(IteratorTest, NullIteratorCurrentItemThrowsException) {
    // Arrange
    NullIterator null_iterator;
    // Act & Assert
    EXPECT_THROW(null_iterator.current_item(), std::runtime_error);
}

TEST_F(IteratorTest, BookBundleIteratorTraversal) {
    // Arrange
    BookBundle bundle(3, "C++ Series");
    bundle.add_item(new Book(1, "Effective C++", "Scott Meyers"));
    bundle.add_item(new EBook(2, "Clean Code", "Robert Martin"));
    // Act
    Iterator* it = bundle.create_iterator();
    // Assert
    EXPECT_NE(dynamic_cast<BookBundleIterator*>(it), nullptr);
    EXPECT_EQ(it->current_item()->get_id(), 1);
    EXPECT_EQ(it->current_item()->get_title(), "Effective C++");
    EXPECT_EQ(it->current_item()->get_author(), "Scott Meyers");
    it->next();
    EXPECT_EQ(it->current_item()->get_id(), 2);
    EXPECT_EQ(it->current_item()->get_title(), "Clean Code");
    EXPECT_EQ(it->current_item()->get_author(), "Robert Martin");
    it->next();
    EXPECT_TRUE(it->is_done());
    delete it;
}

TEST_F(IteratorTest, BookBundleIteratorFirstResetsIndex) {
    // Arrange
    auto bundle = std::make_unique<BookBundle>(1, "C++ Series");
    bundle->add_item(new Book(2, "Effective C++", "Scott Meyers"));
    bundle->add_item(new EBook(3, "Clean Code", "Robert Martin"));
    // Act
    Iterator* it = bundle->create_iterator();
    // Assert
    EXPECT_EQ(it->current_item()->get_id(), 2);
    it->next();
    EXPECT_EQ(it->current_item()->get_id(), 3);
    it->first();
    EXPECT_EQ(it->current_item()->get_id(), 2);
    delete it;
}

TEST_F(IteratorTest, BookBundleIteratorBoundaryThrowsException) {
    // Arrange
    auto bundle = std::make_unique<BookBundle>(1, "C++ Series");
    bundle->add_item(new Book(2, "Effective C++", "Scott Meyers"));
    bundle->add_item(new EBook(3, "Clean Code", "Robert Martin"));
    // Act
    Iterator* it = bundle->create_iterator();
    // Assert
    EXPECT_EQ(it->current_item()->get_id(), 2);
    it->next();
    EXPECT_EQ(it->current_item()->get_id(), 3);
    it->next();
    EXPECT_TRUE(it->is_done());
    EXPECT_THROW(it->next(), std::runtime_error);
    delete it;
}

