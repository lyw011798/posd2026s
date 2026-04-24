#include "null_iterator.h"
#include <stdexcept>

void NullIterator::first() {}

void NullIterator::next() {
    throw std::runtime_error("No next item in NullIterator");
}

bool NullIterator::isDone() const {
    return true;
}

Character* NullIterator::currentItem() const {
    throw std::runtime_error("No current item in NullIterator");
}
