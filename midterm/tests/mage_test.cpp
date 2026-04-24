#include "../src/mage.h"
#include <gtest/gtest.h>
#include <string>
#include <memory>



TEST(MageTest, Constructor) {
    auto cleric = std::make_unique<Mage>(2, 3);

    EXPECT_EQ(cleric->intelligence(), 2.0);
    EXPECT_EQ(cleric->mp(), 3.0);
    EXPECT_EQ(cleric->toString(), "Mage (2.000000 3.000000)");
    EXPECT_EQ(cleric->combatStyleName(), "Magic");
}
