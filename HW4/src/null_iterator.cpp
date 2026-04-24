#include "null_iterator.h"
#include <stdexcept>

void NullIterator::first() {}

void NullIterator::next() {
    throw std::runtime_error("No next item in NullIterator");
}

bool NullIterator::is_done() const {
    return true;
}

LibraryItem* NullIterator::current_item() const {
    throw std::runtime_error("No current item in NullIterator");
}
