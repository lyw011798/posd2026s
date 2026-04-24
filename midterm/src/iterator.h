#ifndef ITERATOR_H
#define ITERATOR_H

class Character;

class Iterator {
public:
    virtual ~Iterator() = default;
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
    virtual Character* currentItem() const = 0;
};

#endif
