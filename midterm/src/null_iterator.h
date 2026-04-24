#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H

#include "iterator.h"

class NullIterator : public Iterator {
public:
    void first() override;
    void next() override;
    bool isDone() const override;
    Character* currentItem() const override;
};

#endif
