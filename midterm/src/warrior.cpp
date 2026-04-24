#include "warrior.h"
#include "combat_strategy.h"
#include "character_visitor.h"

MeleeStrategy* melee;

Warrior::Warrior(double atk, double def) : Character(new MeleeStrategy) {
    if (atk <= 0 || def <= 0){
        throw std::string("It's not a warrior!");
    }
    atk_= atk;
    def_ = def;
}

double Warrior::power() const {
    return atk_*def_;
}

std::string Warrior::toString() const {
    return "Warrior (" + std::to_string(atk()) + " " + std::to_string(def()) + ")";
}

double Warrior::speed() const {
    return atk_ + def_;
}

double Warrior::atk() const {
    return atk_;
}
double Warrior::def() const {
    return def_;
}
 
void Warrior::setAtk(double atk) {
    atk_ = atk;
 }
void Warrior::setDef(double def) {
    def_ = def;
}

void Warrior::accept(CharacterVisitor* visitor) {
    visitor -> visitWarrior(this);
}
