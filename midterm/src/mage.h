#ifndef MAGE_H
#define MAGE_H

#include "character.h"

class Mage : public Character {
public:
    Mage(double intelligence, double mp);
    double power() const override;
    double speed() const override;
    std::string toString() const override;

    // Visitor pattern
    void accept(CharacterVisitor* visitor) override;

    double intelligence() const;
    double mp() const;
    void setIntelligence(double intelligence);
    void setMp(double mp);
private:
    double intelligence_ = 0;
    double mp_ = 0;
};

#endif
