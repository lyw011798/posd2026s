#include "party_iterator.h"
#include <vector>
#include <string>
#include "party.h"

PartyIterator::PartyIterator(Party* party) : _items(party->characters_), _index(0) {
}

void PartyIterator::first() {
    _index = 0;
}

void PartyIterator::next() {
    if (isDone()) {
        throw std::string("No next item in PartyIterator");
    }
    _index++;
}

bool PartyIterator::isDone() const {
    return _index >= _items.size();
}

Character* PartyIterator::currentItem() const {
    if (isDone()) {
        throw std::string("No current item in PartyIterator");
    }
    return _items[_index];
}
