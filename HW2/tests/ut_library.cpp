#include <gtest/gtest.h>
#include <memory>
#include "../src/library_management_system.h"
#include "../src/book.h"

TEST(LibraryManagementSystemTest, InitialState) {
    LibraryManagementSystem lms;
    EXPECT_EQ(lms.get_total_items(), 0);
    EXPECT_TRUE(lms.get_all_items().empty());
}

TEST(LibraryManagementSystemTest, AddAndRetrieveItems) {
    LibraryManagementSystem lms;
    
    auto book1 = std::make_unique<Book>(1, "Book 1", "Author A");
    auto book2 = std::make_unique<Book>(2, "Book 2", "Author B");
    
    lms.add_item(book1.get());
    lms.add_item(book2.get());
    
    EXPECT_EQ(lms.get_total_items(), 2);
    
    auto items = lms.get_all_items();
    ASSERT_EQ(items.size(), 2);
    EXPECT_EQ(items[0]->get_title(), "Book 1");
    EXPECT_EQ(items[1]->get_title(), "Book 2");
}

TEST(LibraryManagementSystemTest, SearchByTitle) {
    LibraryManagementSystem lms;
    auto book1 = std::make_unique<Book>(1, "C++ Primer", "Lippman");
    auto book2 = std::make_unique<Book>(2, "Effective C++", "Meyers");
    auto book3 = std::make_unique<Book>(3, "C++ Primer", "Unknown");

    lms.add_item(book1.get());
    lms.add_item(book2.get());
    lms.add_item(book3.get());

    auto result_primer = lms.search_by_title("C++ Primer");
    ASSERT_EQ(result_primer.size(), 2);
    EXPECT_EQ(result_primer[0]->get_id(), 1);
    EXPECT_EQ(result_primer[1]->get_id(), 3);

    auto result_effective = lms.search_by_title("Effective C++");
    ASSERT_EQ(result_effective.size(), 1);
    EXPECT_EQ(result_effective[0]->get_author(), "Meyers");

    auto result_none = lms.search_by_title("Java");
    EXPECT_TRUE(result_none.empty());
}

TEST(LibraryManagementSystemTest, SearchByAuthor) {
    LibraryManagementSystem lms;
    auto book1 = std::make_unique<Book>(1, "Clean Code", "Robert C. Martin");
    auto book2 = std::make_unique<Book>(2, "Clean Architecture", "Robert C. Martin");
    auto book3 = std::make_unique<Book>(3, "Refactoring", "Martin Fowler");

    lms.add_item(book1.get());
    lms.add_item(book2.get());
    lms.add_item(book3.get());

    auto result_martin = lms.search_by_author("Robert C. Martin");
    ASSERT_EQ(result_martin.size(), 2);
    EXPECT_EQ(result_martin[0]->get_title(), "Clean Code");
    EXPECT_EQ(result_martin[1]->get_title(), "Clean Architecture");

    auto result_fowler = lms.search_by_author("Martin Fowler");
    ASSERT_EQ(result_fowler.size(), 1);
    EXPECT_EQ(result_fowler[0]->get_id(), 3);

    auto result_none = lms.search_by_author("Kent Beck");
    EXPECT_TRUE(result_none.empty());
}

#include "../src/standard_fine_strategy.h"
#include "../src/progressive_fine_strategy.h"
#include "../src/no_fine_strategy.h"

TEST(LibraryManagementSystemTest, CalculateFineWithoutStrategyReturnsZero) {
    LibraryManagementSystem lms;
    auto book = std::make_unique<Book>(1, "Book", "Author");
    lms.add_item(book.get());

    EXPECT_DOUBLE_EQ(lms.calculate_fine(book.get(), 10), 0.0);
}

TEST(LibraryManagementSystemTest, SetAndCalculateFineWithDifferentStrategies) {
    LibraryManagementSystem lms;
    auto book = std::make_unique<Book>(1, "Book", "Author");
    lms.add_item(book.get());

    StandardFineStrategy standard_strategy;
    ProgressiveFineStrategy progressive_strategy;
    NoFineStrategy no_fine_strategy;

    // Standard
    lms.set_fine_strategy(&standard_strategy);
    EXPECT_DOUBLE_EQ(lms.calculate_fine(book.get(), 10), 10.0);

    // Progressive
    lms.set_fine_strategy(&progressive_strategy);
    EXPECT_DOUBLE_EQ(lms.calculate_fine(book.get(), 10), 13.0);

    // No Fine
    lms.set_fine_strategy(&no_fine_strategy);
    EXPECT_DOUBLE_EQ(lms.calculate_fine(book.get(), 10), 0.0);
}
