#include "../src/warrior.h"
#include <gtest/gtest.h>
#include <string>
#include <memory>



TEST(WarriorTest, Constructor) {
    auto cleric = std::make_unique<Warrior>(2, 3);

    EXPECT_EQ(cleric->atk(), 2.0);
    EXPECT_EQ(cleric->def(), 3.0);
    EXPECT_EQ(cleric->toString(), "Warrior (2.000000 3.000000)");
    EXPECT_EQ(cleric->combatStyleName(), "Melee");
}
