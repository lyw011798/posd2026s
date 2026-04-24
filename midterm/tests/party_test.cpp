#include "../src/party.h"
#include "../src/warrior.h"
#include "../src/cleric.h"
#include "../src/mage.h"
#include <gtest/gtest.h>
#include <string>
#include <memory>

TEST(PartyTest, Constructor) {
    auto party = std::make_unique<Party>(new MagicStrategy);
    Party* sub_party = new Party(new MeleeStrategy);

    sub_party->add(new Cleric(2.0, 3.0));
    party->add(new Warrior(2.0, 3.0));
    party->add(new Mage(2.0, 3.0));
    party->add(sub_party);

    EXPECT_EQ(party->speed(), 4.0);
    EXPECT_EQ(party->power(), 18.0);
    EXPECT_EQ(party->toString(), "Party(Warrior (2.000000 3.000000) Mage (2.000000 3.000000) Party(Cleric (2.000000 3.000000) ) )");
    EXPECT_EQ(party->combatStyleName(), "Magic");
}