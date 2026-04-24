#include <gtest/gtest.h>
#include "../src/library_item_visitor.h"
#include "../src/item_count_visitor.h"
#include "../src/fine_calculation_visitor.h"
#include "../src/book.h"
#include "../src/ebook.h"
#include "../src/reference_book.h"
#include "../src/book_bundle.h"

// A simple mock visitor to track which overloaded visit method was called.
class MockVisitor : public LibraryItemVisitor {
public:
    int visited_book_count = 0;
    int visited_ebook_count = 0;
    int visited_reference_book_count = 0;
    int visited_book_bundle_count = 0;

    void visit_book(Book& book) override { visited_book_count++; }
    void visit_ebook(EBook& ebook) override { visited_ebook_count++; }
    void visit_reference_book(ReferenceBook& reference_book) override { visited_reference_book_count++; }
    void visit_book_bundle(BookBundle& book_bundle) override { visited_book_bundle_count++; }
};

class VisitorTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(VisitorTest, BookAcceptDispatchesToVisitBook) {
    // Arrange
    auto visitor = std::make_unique<MockVisitor>();
    auto book = std::make_unique<Book>(1, "Effective C++", "Scott Meyers");

    // Act
    book->accept(*visitor);
    // Assert
    EXPECT_EQ(visitor->visited_book_count, 1);
    EXPECT_EQ(visitor->visited_ebook_count, 0);
    EXPECT_EQ(visitor->visited_reference_book_count, 0);
    EXPECT_EQ(visitor->visited_book_bundle_count, 0);
}

TEST_F(VisitorTest, EBookAcceptDispatchesToVisitEBook) {
    // Arrange
    auto visitor = std::make_unique<MockVisitor>();
    auto ebook = std::make_unique<EBook>(2, "Clean Code", "Robert Martin");

    // Act
    ebook->accept(*visitor);
    // Assert
    EXPECT_EQ(visitor->visited_book_count, 0);
    EXPECT_EQ(visitor->visited_ebook_count, 1);
    EXPECT_EQ(visitor->visited_reference_book_count, 0);
    EXPECT_EQ(visitor->visited_book_bundle_count, 0);
}

TEST_F(VisitorTest, ReferenceBookAcceptDispatchesToVisitReferenceBook) {
    // Arrange
    auto visitor = std::make_unique<MockVisitor>();
    auto reference_book = std::make_unique<ReferenceBook>(3, "Design Patterns", "GoF");

    // Act
    reference_book->accept(*visitor);
    // Assert
    EXPECT_EQ(visitor->visited_book_count, 0);
    EXPECT_EQ(visitor->visited_ebook_count, 0);
    EXPECT_EQ(visitor->visited_reference_book_count, 1);
    EXPECT_EQ(visitor->visited_book_bundle_count, 0);
}

TEST_F(VisitorTest, BookBundleAcceptDispatchesToVisitBookBundle) {
    // Arrange
    auto visitor = std::make_unique<MockVisitor>();
    auto book_bundle = std::make_unique<BookBundle>(4, "C++ Series");

    // Act
    book_bundle->accept(*visitor);
    // Assert
    EXPECT_EQ(visitor->visited_book_count, 0);
    EXPECT_EQ(visitor->visited_ebook_count, 0);
    EXPECT_EQ(visitor->visited_reference_book_count, 0);
    EXPECT_EQ(visitor->visited_book_bundle_count, 1);
}

TEST_F(VisitorTest, ItemCountVisitorWithSingleBook) {
    // Arrange
    auto visitor = std::make_unique<ItemCountVisitor>();
    auto book = std::make_unique<Book>(1, "Clean Code", "Robert Martin");

    // Act
    book->accept(*visitor);

    // Assert
    EXPECT_EQ(visitor->get_book_count(), 1);
    EXPECT_EQ(visitor->get_ebook_count(), 0);
    EXPECT_EQ(visitor->get_reference_book_count(), 0);
    EXPECT_EQ(visitor->get_bundle_count(), 0);
    EXPECT_EQ(visitor->get_total_count(), 1);
}

TEST_F(VisitorTest, ItemCountVisitorWithNestedBundle) {
    // Arrange
    auto visitor = std::make_unique<ItemCountVisitor>();
    auto root = std::make_unique<BookBundle>(1, "Root Bundle");
    auto sub = std::make_unique<BookBundle>(2, "Sub Bundle");
    
    root->add_item(new Book(3, "B1", "A1"));
    root->add_item(sub.get());
    sub->add_item(new EBook(4, "E1", "A2"));
    sub->add_item(new ReferenceBook(5, "R1", "A3"));
    sub->add_item(new Book(6, "B2", "A4"));

    // Act
    root->accept(*visitor);

    // Assert
    EXPECT_EQ(visitor->get_book_count(), 2);
    EXPECT_EQ(visitor->get_ebook_count(), 1);
    EXPECT_EQ(visitor->get_reference_book_count(), 1);
    EXPECT_EQ(visitor->get_bundle_count(), 2);
    EXPECT_EQ(visitor->get_total_count(), 4);
}

TEST_F(VisitorTest, ItemCountVisitorWithEmptyBundle) {
    // Arrange
    auto visitor = std::make_unique<ItemCountVisitor>();
    auto bundle = std::make_unique<BookBundle>(1, "Empty Bundle");

    // Act
    bundle->accept(*visitor);

    // Assert
    EXPECT_EQ(visitor->get_book_count(), 0);
    EXPECT_EQ(visitor->get_ebook_count(), 0);
    EXPECT_EQ(visitor->get_reference_book_count(), 0);
    EXPECT_EQ(visitor->get_bundle_count(), 1);
    EXPECT_EQ(visitor->get_total_count(), 0);
}

TEST_F(VisitorTest, ItemCountVisitorWithFlatBundle) {
    // Arrange
    auto visitor = std::make_unique<ItemCountVisitor>();
    auto bundle = std::make_unique<BookBundle>(1, "Flat Bundle");
    
    bundle->add_item(new Book(2, "B1", "A1"));
    bundle->add_item(new EBook(3, "E1", "A2"));
    bundle->add_item(new ReferenceBook(4, "R1", "A3"));

    // Act
    bundle->accept(*visitor);

    // Assert
    EXPECT_EQ(visitor->get_book_count(), 1);
    EXPECT_EQ(visitor->get_ebook_count(), 1);
    EXPECT_EQ(visitor->get_reference_book_count(), 1);
    EXPECT_EQ(visitor->get_bundle_count(), 1);
    EXPECT_EQ(visitor->get_total_count(), 3);
}



TEST_F(VisitorTest, FineCalculationVisitorWithSingleBook) {
    // Arrange
    auto visitor = std::make_unique<FineCalculationVisitor>(5); // 5 days overdue
    auto book = std::make_unique<Book>(1, "B1", "A1");

    // Act
    book->accept(*visitor);

    // Assert
    // Book fine: 1.0 * 5 = 5.0
    EXPECT_DOUBLE_EQ(visitor->get_total_fine(), 5.0);
}

TEST_F(VisitorTest, FineCalculationVisitorWithFlatBundle) {
    // Arrange
    auto visitor = std::make_unique<FineCalculationVisitor>(3); // 3 days overdue
    auto root = std::make_unique<BookBundle>(1, "Root");
    root->add_item(new Book(2, "B1", "A1"));           // 1.0 * 3 = 3.0
    root->add_item(new EBook(3, "E1", "A2"));          // 0.5 * 3 = 1.5
    root->add_item(new ReferenceBook(4, "R1", "A3"));  // 2.0 * 3 = 6.0
    
    // Act
    root->accept(*visitor);

    // Assert
    // Total fine: 3.0 + 1.5 + 6.0 = 10.5
    EXPECT_DOUBLE_EQ(visitor->get_total_fine(), 10.5);
}

TEST_F(VisitorTest, FineCalculationVisitorWithZeroOverdue) {
    // Arrange
    auto visitor = std::make_unique<FineCalculationVisitor>(0);
    auto book = std::make_unique<Book>(1, "B1", "A1");

    // Act
    book->accept(*visitor);

    // Assert
    EXPECT_DOUBLE_EQ(visitor->get_total_fine(), 0.0);
}

TEST_F(VisitorTest, FineCalculationVisitorWithNestedBundle) {
    // Arrange
    auto visitor = std::make_unique<FineCalculationVisitor>(2); // 2 days overdue
    auto root = std::make_unique<BookBundle>(1, "Root");
    auto sub = std::make_unique<BookBundle>(2, "Sub");
    
    root->add_item(new Book(3, "B1", "A1"));           // 1.0 * 2 = 2.0
    root->add_item(sub.get());
    sub->add_item(new EBook(4, "E1", "A2"));          // 0.5 * 2 = 1.0
    sub->add_item(new ReferenceBook(5, "R1", "A3"));  // 2.0 * 2 = 4.0

    // Act
    root->accept(*visitor);

    // Assert
    // Total fine: 2.0 + 1.0 + 4.0 = 7.0
    EXPECT_DOUBLE_EQ(visitor->get_total_fine(), 7.0);
}



