#include "party.h"
#include "combat_strategy.h"
#include "character_visitor.h"
#include "math.h"
#include "party_iterator.h"


Party::Party(CombatStrategy* combatStyle) : Character(combatStyle) {
}

double Party::power() const {
    double totalPower = 0;
    for (const auto& cha : characters_) {
        totalPower += cha->power();
    }
    return totalPower;
}

std::string Party::toString() const {
    std::string result = "Party(";
    for (auto item : characters_) {
        std::string child_str = item->toString();
        result += child_str;
        result += " ";
    }
    result = result + ")";
    return result;

}

void Party::add(Character* character) {
    characters_.push_back(character);
}

double Party::speed() const {
    double min = MAXFLOAT;
    for(int i = 0 ; i < characters_.size(); ++i){
        if(characters_[i]->speed() < min){
            min = characters_[i]->speed();
        }
    }

    return min;
}

Iterator* Party::createIterator() {
    return new PartyIterator(this);
}

void Party::accept(CharacterVisitor* visitor) {
    visitor -> visitParty(this);
}
