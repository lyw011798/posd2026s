#ifndef CLERIC_H
#define CLERIC_H

#include "character.h"

class Cleric : public Character {
public:
    Cleric(double faith, double hp);
    double power() const override;
    double speed() const override;
    std::string toString() const override;

    // Visitor pattern
    void accept(CharacterVisitor* visitor) override;

    double faith() const;
    double hp() const;
    void setFaith(double faith);
    void setHp(double hp);
private:
    double faith_ = 0;
    double hp_ = 0;
};

#endif
