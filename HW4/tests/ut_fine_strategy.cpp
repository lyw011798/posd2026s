#include <gtest/gtest.h>
#include <string>
#include <memory>
#include "../src/fine_strategy.h"
#include "../src/library_item.h"
#include "../src/book_bundle.h"
#include "../src/library_item_visitor.h"

// Define a StrategyMockLibraryItem to isolate the test from concrete items like Book
class StrategyMockLibraryItem : public LibraryItem {
public:
    StrategyMockLibraryItem() : LibraryItem(1, "MockTitle", "MockAuthor") {}
    std::string get_type() override { return "MockType"; }
    std::string to_string() override { return "MockType: MockTitle by MockAuthor"; }
    void accept(LibraryItemVisitor& visitor) override {}
};

// Define a MockFineStrategy to test the interface
class MockFineStrategy : public FineStrategy {
public:
    double calculate_fine(LibraryItem* item, int days_overdue) const override { 
        return (days_overdue > 0) ? 10.0 : 0.0; 
    }
    std::string name() const override { return "MockFineStrategy"; }
};

TEST(FineStrategyTest, MockBehavior) {
    // Arrange
    auto strategy = std::make_unique<MockFineStrategy>();
    auto item = std::make_unique<StrategyMockLibraryItem>();

    // Act & Assert
    EXPECT_EQ(strategy->name(), "MockFineStrategy");
    EXPECT_EQ(strategy->calculate_fine(item.get(), 5), 10.0);
    EXPECT_EQ(strategy->calculate_fine(item.get(), 0), 0.0);
    EXPECT_EQ(strategy->calculate_fine(item.get(), -1), 0.0);
}

#include "../src/standard_fine_strategy.h"
#include "../src/book.h"
#include "../src/reference_book.h"
#include "../src/ebook.h"

TEST(StandardFineStrategyTest, CalculateFineForDifferentItems) {
    StandardFineStrategy strategy;
    
    auto book = std::make_unique<Book>(1, "Book", "Author");
    auto ref_book = std::make_unique<ReferenceBook>(2, "Ref", "Author");
    auto ebook = std::make_unique<EBook>(3, "EBook", "Author");

    // Book: $1.0 per day
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(book.get(), 1), 1.0);
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(book.get(), 5), 5.0);

    // ReferenceBook: $2.0 per day
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(ref_book.get(), 1), 2.0);
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(ref_book.get(), 5), 10.0);

    // EBook: $0.5 per day
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(ebook.get(), 1), 0.5);
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(ebook.get(), 4), 2.0);
}

TEST(StandardFineStrategyTest, ZeroOrNegativeDaysShouldReturnZero) {
    StandardFineStrategy strategy;
    auto book = std::make_unique<Book>(1, "Book", "Author");

    EXPECT_DOUBLE_EQ(strategy.calculate_fine(book.get(), 0), 0.0);
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(book.get(), -5), 0.0);
}

TEST(StandardFineStrategyTest, NameReturnsCorrectString) {
    StandardFineStrategy strategy;
    EXPECT_EQ(strategy.name(), "StandardFineStrategy");
}

TEST(StandardFineStrategyTest, CalculateFineForBookBundle) {
    StandardFineStrategy strategy;
    
    auto bundle = std::make_unique<BookBundle>(100, "Bundle");
    auto book = std::make_unique<Book>(1, "Book", "Author");
    auto ebook = std::make_unique<EBook>(3, "EBook", "Author");

    EXPECT_DOUBLE_EQ(strategy.calculate_fine(bundle.get(), 5), 0.0);

    bundle->add_item(book.get());
    bundle->add_item(ebook.get());

    EXPECT_DOUBLE_EQ(strategy.calculate_fine(bundle.get(), 5), 7.5);

    auto nested = std::make_unique<BookBundle>(101, "Nested");
    auto ref_book = std::make_unique<ReferenceBook>(2, "Ref", "Author");
    nested->add_item(ref_book.get());
    bundle->add_item(nested.get());

    EXPECT_DOUBLE_EQ(strategy.calculate_fine(bundle.get(), 5), 17.5);
}

#include "../src/progressive_fine_strategy.h"

TEST(ProgressiveFineStrategyTest, CalculateFineForDifferentItemsUnderAndOver7Days) {
    ProgressiveFineStrategy strategy;
    
    auto book = std::make_unique<Book>(1, "Book", "Author");
    auto ref_book = std::make_unique<ReferenceBook>(2, "Ref", "Author");
    auto ebook = std::make_unique<EBook>(3, "EBook", "Author");

    // Book (Base $1.0)
    // <= 7 days: 1.0 * days
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(book.get(), 1), 1.0);
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(book.get(), 7), 7.0);
    // > 7 days: 7.0 + (days - 7) * 2.0
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(book.get(), 8), 9.0);
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(book.get(), 10), 13.0);

    // ReferenceBook (Base $2.0)
    // <= 7 days: 2.0 * days
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(ref_book.get(), 7), 14.0);
    // > 7 days: 14.0 + (days - 7) * 4.0
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(ref_book.get(), 8), 18.0);

    // EBook (Base $0.5)
    // <= 7 days: 0.5 * days
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(ebook.get(), 7), 3.5);
    // > 7 days: 3.5 + (days - 7) * 1.0
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(ebook.get(), 8), 4.5);
}

TEST(ProgressiveFineStrategyTest, ZeroOrNegativeDaysShouldReturnZero) {
    ProgressiveFineStrategy strategy;
    auto book = std::make_unique<Book>(1, "Book", "Author");

    EXPECT_DOUBLE_EQ(strategy.calculate_fine(book.get(), 0), 0.0);
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(book.get(), -5), 0.0);
}

TEST(ProgressiveFineStrategyTest, NameReturnsCorrectString) {
    ProgressiveFineStrategy strategy;
    EXPECT_EQ(strategy.name(), "ProgressiveFineStrategy");
}

TEST(ProgressiveFineStrategyTest, CalculateFineForBookBundle) {
    ProgressiveFineStrategy strategy;

    auto bundle = std::make_unique<BookBundle>(100, "Bundle");
    auto book = std::make_unique<Book>(1, "Book", "Author"); 
    auto ref_book = std::make_unique<ReferenceBook>(2, "Ref", "Author");

    bundle->add_item(book.get());
    
    auto nested = std::make_unique<BookBundle>(101, "Nested");
    nested->add_item(ref_book.get());
    bundle->add_item(nested.get());

    EXPECT_DOUBLE_EQ(strategy.calculate_fine(bundle.get(), 8), 27.0);
}

#include "../src/no_fine_strategy.h"

TEST(NoFineStrategyTest, AlwaysReturnsZero) {
    NoFineStrategy strategy;
    
    auto book = std::make_unique<Book>(1, "Book", "Author");
    auto ref_book = std::make_unique<ReferenceBook>(2, "Ref", "Author");
    auto ebook = std::make_unique<EBook>(3, "EBook", "Author");

    EXPECT_DOUBLE_EQ(strategy.calculate_fine(book.get(), 10), 0.0);
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(ref_book.get(), 100), 0.0);
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(ebook.get(), 1), 0.0);
    EXPECT_DOUBLE_EQ(strategy.calculate_fine(book.get(), -5), 0.0);
}

TEST(NoFineStrategyTest, NameReturnsCorrectString) {
    NoFineStrategy strategy;
    EXPECT_EQ(strategy.name(), "NoFineStrategy");
}
