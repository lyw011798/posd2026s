#ifndef PARTY_H
#define PARTY_H

#include "character.h"
#include <vector>

class Party : public Character {
    friend class PartyIterator;

public:
    Party(CombatStrategy* combatStyle);

    double power() const override;
    double speed() const override;
    std::string toString() const override;

    // Composite pattern
    void add(Character* character) override;

    // Iterator pattern
    Iterator* createIterator() override;

    // Visitor pattern
    void accept(CharacterVisitor* visitor) override;
private:
    std::vector<Character*> characters_;
    size_t _index;
};

#endif
