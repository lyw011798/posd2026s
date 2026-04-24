#include "buff_visitor.h"
#include "cleric.h"
#include "warrior.h"
#include "mage.h"
#include "party.h"
#include "party_iterator.h"



void BuffVisitor::visitWarrior(Warrior* warrior) {
    warrior->setAtk(warrior->atk() * 1.5);
}

void BuffVisitor::visitMage(Mage* mage) {
    mage->setIntelligence(mage->intelligence() * 1.3);
}

void BuffVisitor::visitCleric(Cleric* reference_book) {
    reference_book->setFaith(reference_book->faith() * 1.2);
}

void BuffVisitor::visitParty(Party* party) {
    PartyIterator* partyIt = new PartyIterator(party);
    while ( !partyIt->isDone()) {
        partyIt->currentItem()->accept(this);
    }
}

