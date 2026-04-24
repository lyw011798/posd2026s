#ifndef CHARACTER_H
#define CHARACTER_H

#include "combat_strategy.h"
#include <string>

class CharacterVisitor;
class Iterator;

class Character {
public:
    Character(CombatStrategy* combatStyle);

    virtual double power() const = 0;
    virtual double speed() const = 0;
    virtual std::string toString() const = 0;
    
    // Strategy pattern
    void setCombatStyle(CombatStrategy* style);
    std::string combatStyleName() const;
    double attack(double targetDef) const;
    
    // Composite pattern
    virtual void add(Character* character);
    
    // Iterator pattern
    virtual Iterator* createIterator();
    
    // Visitor pattern
    virtual void accept(CharacterVisitor* visitor);
private:
    CombatStrategy* combatStyle_ = nullptr;
};

#endif
