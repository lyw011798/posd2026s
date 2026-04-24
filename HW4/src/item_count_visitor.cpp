#include "item_count_visitor.h"
#include "book.h"
#include "ebook.h"
#include "reference_book.h"
#include "book_bundle.h"
#include "book_bundle_iterator.h"

ItemCountVisitor::ItemCountVisitor()
    : _book_count(0), _ebook_count(0), _reference_book_count(0), _bundle_count(0) {}

void ItemCountVisitor::visit_book(Book& book) {
    _book_count++;
}

void ItemCountVisitor::visit_ebook(EBook& ebook) {
    _ebook_count++;
}

void ItemCountVisitor::visit_reference_book(ReferenceBook& reference_book) {
    _reference_book_count++;
}

void ItemCountVisitor::visit_book_bundle(BookBundle& book_bundle) {
    Iterator* it = book_bundle.create_iterator();
    while (!it->is_done()) {
        LibraryItem* item = it->current_item();
        item->accept(*this);
        it->next();
    }
    delete it;
    _bundle_count++;
}

int ItemCountVisitor::get_book_count() const {
    return _book_count;
}

int ItemCountVisitor::get_ebook_count() const {
    return _ebook_count;
}

int ItemCountVisitor::get_reference_book_count() const {
    return _reference_book_count;
}

int ItemCountVisitor::get_bundle_count() const {
    return _bundle_count;
}

int ItemCountVisitor::get_total_count() const {
    return _book_count + _ebook_count + _reference_book_count;
}
