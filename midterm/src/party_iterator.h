#ifndef PARTY_ITERATOR_H
#define PARTY_ITERATOR_H

#include "iterator.h"
#include <vector>

class Party;

class PartyIterator : public Iterator {
public:
    PartyIterator(Party* party);
    void first() override;
    void next() override;
    bool isDone() const override;
    Character* currentItem() const override;
private:
    std::vector<Character*> _items;
    int _index;
};

#endif
