#include "combat_strategy.h"
#include "math.h"



double MeleeStrategy::damage(double powerOfCharacter, double targetDefense) const {
    return std::max(0.0, powerOfCharacter * 1.2 - targetDefense);
}

std::string MeleeStrategy::name() const {
    return "Melee";
}


double MagicStrategy::damage(double powerOfCharacter, double targetDefense) const {
    return (powerOfCharacter * 2.0);
}

std::string MagicStrategy::name() const {
    return "Magic";
}

double HealStrategy::damage(double powerOfCharacter, double targetDefense) const {
    return (powerOfCharacter * -0.8);
}

std::string HealStrategy::name() const {
    return "Heal";
}


double CombatStrategy::damage(double powerOfCharacter, double targetDefense) const{
    return 0.0;
}

std::string CombatStrategy::name() const {
    return "CombatStrategy";
}