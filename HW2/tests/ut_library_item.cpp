#include <gtest/gtest.h>
#include <string>
#include <memory>
#include "../src/library_item.h"

// We need a mock class to test LibraryItem because it is an abstract base class
class MockLibraryItem : public LibraryItem {
public:
    MockLibraryItem(long id, std::string title, std::string author)
        : LibraryItem(id, title, author) {}

    std::string get_type() override { return "MockType"; }
    std::string to_string() override { return "MockToString"; }
};

TEST(LibraryItemTest, ConstructorAndGetters) {
    //Arrange
    auto item = std::make_unique<MockLibraryItem>(1, "Clean Code", "Robert Martin");

    //Act & Assert
    EXPECT_EQ(item->get_id(), 1);
    EXPECT_EQ(item->get_title(), "Clean Code");
    EXPECT_EQ(item->get_author(), "Robert Martin");
}

TEST(LibraryItemTest, GetType) {
    //Arrange: Create the mock item, but hold it in a LibraryItem pointer to test virtual dispatch
    std::unique_ptr<LibraryItem> item = std::make_unique<MockLibraryItem>(1, "Clean Code", "Robert Martin");

    //Act
    std::string type = item->get_type();

    //Assert
    EXPECT_EQ(type, "MockType");
}

TEST(LibraryItemTest, ToString) {
    //Arrange: Create the mock item, but hold it in a LibraryItem pointer to test virtual dispatch
    std::unique_ptr<LibraryItem> item = std::make_unique<MockLibraryItem>(1, "Clean Code", "Robert Martin");

    //Act
    std::string str = item->to_string();

    //Assert
    EXPECT_EQ(str, "MockToString");
}
