#include <gtest/gtest.h>
#include <cmath>
#include <string>
#include "triangle.h"

TEST(TriangleTest, ConstructorValid) {
    EXPECT_NO_THROW(Triangle t(3.0, 4.0, 5.0));
}

TEST(TriangleTest, Area) {
    Triangle t(3.0, 4.0, 5.0);
    // Heron's formula: s = (3+4+5)/2 = 6, Area = sqrt(6*(6-3)*(6-4)*(6-5)) = sqrt(36) = 6
    EXPECT_EQ(t.area(), 6.0);
}

TEST(TriangleTest, AreaNonInteger) {
    Triangle t(3.1, 4.2, 5.3);
    // s = (3.1 + 4.2 + 5.3) / 2 = 6.3
    // Area = sqrt(6.3 * (6.3-3.1) * (6.3-4.2) * (6.3-5.3)) = sqrt(6.3 * 3.2 * 2.1 * 1.0) = sqrt(42.336)
    EXPECT_NEAR(t.area(), 6.506612, 0.0001);
}

TEST(TriangleTest, Perimeter) {
    Triangle t(3.0, 4.0, 5.0);
    EXPECT_EQ(t.perimeter(), 12.0);
}

TEST(TriangleTest, ToString) {
    Triangle t(3.0, 4.0, 5.0);
    EXPECT_EQ(t.toString(), "Triangle (3 4 5)");
}

TEST(TriangleTest, ToStringNonInteger) {
    Triangle t(3.1, 4.2, 5.3);
    EXPECT_EQ(t.toString(), "Triangle (3.1 4.2 5.3)");
}

TEST(TriangleTest, ConstructorInvalidSidesThrows) {
    try {
        Triangle t(1.0, 1.0, 3.0);
        FAIL() << "Should throw std::string";
    } catch (const std::string& e) {
        EXPECT_EQ(e, "It's not a triangle!");
    } catch (...) {
        FAIL() << "Should throw std::string";
    }
}

TEST(TriangleTest, ConstructorNegativeSideThrows) {
    try {
        Triangle t(-3.0, 4.0, 5.0);
        FAIL() << "Should throw std::string";
    } catch (const std::string& e) {
        EXPECT_EQ(e, "It's not a triangle!");
    } catch (...) {
        FAIL() << "Should throw std::string";
    }
}

TEST(TriangleTest, ConstructorZeroSideThrows) {
    try {
        Triangle t(3.0, 0.0, 5.0);
        FAIL() << "Should throw std::string";
    } catch (const std::string& e) {
        EXPECT_EQ(e, "It's not a triangle!");
    } catch (...) {
        FAIL() << "Should throw std::string";
    }
}
