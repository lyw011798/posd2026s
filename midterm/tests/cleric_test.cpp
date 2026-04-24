#include "../src/cleric.h"
#include <gtest/gtest.h>
#include <string>
#include <memory>


TEST(ClericTest, Constructor) {
    auto cleric = std::make_unique<Cleric>(2, 3);

    EXPECT_EQ(cleric->faith(), 2.0);
    EXPECT_EQ(cleric->hp(), 3.0);
    EXPECT_EQ(cleric->toString(), "Cleric (2.000000 3.000000)");
    EXPECT_EQ(cleric->combatStyleName(), "Heal");
}








