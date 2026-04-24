#ifndef CHARACTER_VISITOR_H
#define CHARACTER_VISITOR_H

class Warrior;
class Mage;
class Cleric;
class Party;

class CharacterVisitor {
public:
    virtual ~CharacterVisitor() = default;
    virtual void visitWarrior(Warrior* warrior) = 0;
    virtual void visitMage(Mage* mage) = 0;
    virtual void visitCleric(Cleric* cleric) = 0;
    virtual void visitParty(Party* party) = 0;
};

#endif
