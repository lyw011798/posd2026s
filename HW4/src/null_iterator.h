#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H

#include "iterator.h"

class NullIterator : public Iterator {
public:
    void first() override;
    void next() override;
    bool is_done() const override;
    LibraryItem* current_item() const override;
};

#endif // NULL_ITERATOR_H
