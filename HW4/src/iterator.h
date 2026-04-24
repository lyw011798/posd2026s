#ifndef ITERATOR_H
#define ITERATOR_H

#include "library_item.h"

class Iterator {
public:
    virtual ~Iterator() = default;

    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool is_done() const = 0;
    virtual LibraryItem* current_item() const = 0;
};

#endif // ITERATOR_H
