#ifndef LIBRARY_ITEM_VISITOR_H
#define LIBRARY_ITEM_VISITOR_H

class Book;
class EBook;
class ReferenceBook;
class BookBundle;

class LibraryItemVisitor {
public:
    virtual ~LibraryItemVisitor() = default;

    virtual void visit_book(Book& book) = 0;
    virtual void visit_ebook(EBook& ebook) = 0;
    virtual void visit_reference_book(ReferenceBook& reference_book) = 0;
    virtual void visit_book_bundle(BookBundle& book_bundle) = 0;
};

#endif // LIBRARY_ITEM_VISITOR_H
