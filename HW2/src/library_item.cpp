#include "library_item.h"
#include <stdexcept>

LibraryItem::LibraryItem(long id, std::string title, std::string author)
    : id_(id), title_(title), author_(author) {
    if (id <= 0 || title.empty() || author.empty()) {
        throw std::invalid_argument("Invalid LibraryItem parameters");
    }
}

long LibraryItem::get_id() {
    return id_;
}

std::string LibraryItem::get_title() {
    return title_;
}

std::string LibraryItem::get_author() {
    return author_;
}
