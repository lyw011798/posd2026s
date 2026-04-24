#include "book_bundle.h"

BookBundle::BookBundle(long id, std::string title) : LibraryItem(id, title, "Multiple Authors") {}

std::string BookBundle::get_type() {
    return "BookBundle";
}

std::string BookBundle::to_string() {
    std::string result = "Bundle: " + get_title() + " (items: " + std::to_string(_items.size()) + ")";
    for (auto item : _items) {
        std::string child_str = item->to_string();
        result += "\n  ";
        size_t pos = 0;
        while ((pos = child_str.find('\n', pos)) != std::string::npos) {
            child_str.replace(pos, 1, "\n  ");
            pos += 3;
        }
        result += child_str;
    }
    return result;
}

void BookBundle::add_item(LibraryItem* item) {
    _items.push_back(item);
}

const std::vector<LibraryItem*>& BookBundle::get_items() const {
    return _items;
}
