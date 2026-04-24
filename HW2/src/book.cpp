#include "book.h"

Book::Book(long id, std::string title, std::string author)
    : LibraryItem(id, title, author) {}

std::string Book::get_type() {
    return "Book";
}

std::string Book::to_string() {
    return get_type() + ": " + get_title() + " by " + get_author();
}
