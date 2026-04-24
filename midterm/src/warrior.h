#ifndef WARRIOR_H
#define WARRIOR_H

#include "character.h"

class Warrior : public Character {
public:
    Warrior(double atk, double def);
    double power() const override;
    double speed() const override;
    std::string toString() const override;

    // Visitor pattern
    void accept(CharacterVisitor* visitor) override;

    double atk() const;
    double def() const;
    void setAtk(double atk);
    void setDef(double def);
private: 
    double atk_ = 0;
    double def_ = 0;
};

#endif
