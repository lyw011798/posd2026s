#include "library_item.h"
#include "null_iterator.h"
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

void LibraryItem::add_item(LibraryItem* item) {
    throw std::runtime_error("Leaf nodes cannot contain children");
}

Iterator* LibraryItem::create_iterator() {
    return new NullIterator();
}
