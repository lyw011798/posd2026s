#include "cleric.h"
#include "combat_strategy.h"
#include "character_visitor.h"
#include <string>
#include <iostream>

HealStrategy* heal;

Cleric::Cleric(double faith, double hp) : Character(new HealStrategy) {
    if (faith <= 0 || hp <= 0){
        throw std::string("It's not a cleric!");
    }
    faith_= faith;
    hp_ = hp;
}

double Cleric::power() const {
    return faith_*hp_;
}

double Cleric::speed() const {
    return faith_ + hp_;
}

std::string Cleric::toString() const {
    return "Cleric (" + std::to_string(faith()) + " " + std::to_string(hp()) + ")";
}

double Cleric::faith() const {
    return faith_;
}
double Cleric::hp() const {
    return hp_;
}
 
void Cleric::setFaith(double faith) {
    faith_ = faith;
 }
void Cleric::setHp(double hp) {
    hp_ = hp;
}

void Cleric::accept(CharacterVisitor* visitor) {
    visitor -> visitCleric(this);
}
