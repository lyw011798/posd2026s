#ifndef BOOK_BUNDLE_ITERATOR_H
#define BOOK_BUNDLE_ITERATOR_H

#include "iterator.h"
#include <vector>

class BookBundleIterator : public Iterator {
public:
    BookBundleIterator(const std::vector<LibraryItem*>& items);

    void first() override;
    void next() override;
    bool is_done() const override;
    LibraryItem* current_item() const override;

private:
    const std::vector<LibraryItem*>& _items;
    size_t _index;
};

#endif // BOOK_BUNDLE_ITERATOR_H
