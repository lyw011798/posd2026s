#include "mage.h"
#include "combat_strategy.h"
#include "character_visitor.h"

MagicStrategy* magic;

Mage::Mage(double intelligence, double mp) : Character(new MagicStrategy) {
    if (intelligence <= 0 || mp <= 0){
        throw std::string("It's not a Mage!");
    }
    intelligence_= intelligence;
    mp_ = mp;
}

double Mage::power() const {
    return intelligence_*mp_;
}

double Mage::speed() const {
    return intelligence_*2;
}


double Mage::intelligence() const {
    return intelligence_;
}
 double Mage::mp() const {
    return mp_;
}
 
void Mage::setIntelligence(double intelligence) {
    intelligence_ = intelligence;
 }
void Mage::setMp(double mp) {
    mp_ = mp;
}

void Mage::accept(CharacterVisitor* visitor) {
    visitor -> visitMage(this);
}


std::string Mage::toString() const {
    return "Mage (" + std::to_string(intelligence()) + " " + std::to_string(mp()) + ")";
}