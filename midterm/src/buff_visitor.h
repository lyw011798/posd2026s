#ifndef BUFF_VISITOR_H
#define BUFF_VISITOR_H

#include "character_visitor.h"

class BuffVisitor : public CharacterVisitor {
public:
    void visitWarrior(Warrior* warrior) override;
    void visitMage(Mage* mage) override;
    void visitCleric(Cleric* cleric) override;
    void visitParty(Party* party) override;
};

#endif
