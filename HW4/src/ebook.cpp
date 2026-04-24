#include "library_item_visitor.h"
#include "ebook.h"

EBook::EBook(long id, std::string title, std::string author)
    : LibraryItem(id, title, author) {}

std::string EBook::get_type() {
    return "EBook";
}

std::string EBook::to_string() {
    return get_type() + ": " + get_title() + " by " + get_author();
}

void EBook::accept(LibraryItemVisitor& visitor) {
    visitor.visit_ebook(*this);
}
