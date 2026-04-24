#include <gtest/gtest.h>
#include <string>
#include "circle.h"

TEST(CircleTest, ConstructorValidRadius) {
    EXPECT_NO_THROW(Circle c(5.0));
}

TEST(CircleTest, Area) {
    Circle c(5.0);
    EXPECT_NEAR(c.area(), 78.5398163397, 0.0001);
}

TEST(CircleTest, Perimeter) {
    Circle c(5.0);
    EXPECT_NEAR(c.perimeter(), 31.4159265359, 0.0001);
}

TEST(CircleTest, ToStringInteger) {
    Circle c(5.0);
    EXPECT_EQ(c.toString(), "Circle (5)");
}

TEST(CircleTest, ToStringNonInteger) {
    Circle c(5.12);
    EXPECT_EQ(c.toString(), "Circle (5.12)");
}

TEST(CircleTest, ConstructorZeroRadiusThrows) {
    try {
        Circle c(0.0);
        FAIL() << "Should throw std::string";
    } catch (const std::string& e) {
        EXPECT_EQ(e, "It's not a circle!");
    } catch (...) {
        FAIL() << "Should throw std::string";
    }
}

TEST(CircleTest, ConstructorNegativeRadiusThrows) {
    try {
        Circle c(-1.0);
        FAIL() << "Should throw std::string";
    } catch (const std::string& e) {
        EXPECT_EQ(e, "It's not a circle!");
    } catch (...) {
        FAIL() << "Should throw std::string";
    }
}
