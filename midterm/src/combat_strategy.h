#ifndef COMBAT_STRATEGY_H
#define COMBAT_STRATEGY_H

#include <string>
#include <algorithm>

class CombatStrategy {
public:
    virtual ~CombatStrategy() = default;
    virtual double damage(double powerOfCharacter, double targetDefense) const = 0;
    virtual std::string name() const = 0;
};

class MeleeStrategy : public CombatStrategy {
public:
    double damage(double powerOfCharacter, double targetDefense) const override;
    std::string name() const override;
};

class MagicStrategy : public CombatStrategy {
public:
    double damage(double powerOfCharacter, double targetDefense) const override;
    std::string name() const override;
};

class HealStrategy : public CombatStrategy {
public:
    double damage(double powerOfCharacter, double targetDefense) const override;
    std::string name() const override;
};

#endif
