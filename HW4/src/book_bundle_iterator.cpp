#include "book_bundle_iterator.h"
#include <stdexcept>

BookBundleIterator::BookBundleIterator(const std::vector<LibraryItem*>& items) : _items(items), _index(0) {}

void BookBundleIterator::first() {
    _index = 0;
}

void BookBundleIterator::next() {
    if (is_done()) {
        throw std::runtime_error("No next item in BookBundleIterator");
    }
    _index++;
}

bool BookBundleIterator::is_done() const {
    return _index >= _items.size();
}

LibraryItem* BookBundleIterator::current_item() const {
    if (is_done()) {
        throw std::runtime_error("No current item in BookBundleIterator");
    }
    return _items[_index];
}
