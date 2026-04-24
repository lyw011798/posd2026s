#ifndef ITEM_COUNT_VISITOR_H
#define ITEM_COUNT_VISITOR_H

#include "library_item_visitor.h"

class ItemCountVisitor : public LibraryItemVisitor {
public:
    ItemCountVisitor();

    void visit_book(Book& book) override;
    void visit_ebook(EBook& ebook) override;
    void visit_reference_book(ReferenceBook& reference_book) override;
    void visit_book_bundle(BookBundle& book_bundle) override;

    int get_book_count() const;
    int get_ebook_count() const;
    int get_reference_book_count() const;
    int get_bundle_count() const;
    int get_total_count() const;

private:
    int _book_count;
    int _ebook_count;
    int _reference_book_count;
    int _bundle_count;
};

#endif // ITEM_COUNT_VISITOR_H
