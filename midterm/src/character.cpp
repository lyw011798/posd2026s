#include "character.h"
#include <stdexcept>
#include "null_iterator.h"
#include "character_visitor.h"

Character::Character(CombatStrategy* combatStyle) : combatStyle_(combatStyle){
}

std::string Character::toString() const{
    return "Cahrater";
}

double Character::power() const {
    return 0;
}

double Character::speed() const {
    return 0;
}

void Character::setCombatStyle(CombatStrategy* style) {
    combatStyle_ = style;
}

std::string Character::combatStyleName() const {
    return combatStyle_->name();
}

double Character::attack(double targetDef) const {
    return combatStyle_ -> damage( 0, targetDef);
}

Iterator* Character::createIterator() {
    return new NullIterator();
}

void Character::add(Character* character) {
   throw std::string("Cannot add to a leaf character!");
}

void Character::accept(CharacterVisitor* visitor) {
    
}