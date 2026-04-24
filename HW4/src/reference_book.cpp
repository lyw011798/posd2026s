#include "library_item_visitor.h"
#include "reference_book.h"

ReferenceBook::ReferenceBook(long id, std::string title, std::string author)
    : LibraryItem(id, title, author) {}

std::string ReferenceBook::get_type() {
    return "ReferenceBook";
}

std::string ReferenceBook::to_string() {
    return get_type() + ": " + get_title() + " by " + get_author();
}

void ReferenceBook::accept(LibraryItemVisitor& visitor) {
    visitor.visit_reference_book(*this);
}
