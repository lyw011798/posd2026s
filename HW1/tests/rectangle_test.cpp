#include <gtest/gtest.h>
#include <string>
#include "rectangle.h"

TEST(RectangleTest, ConstructorValid) {
    EXPECT_NO_THROW(Rectangle r(3.0, 4.0));
}

TEST(RectangleTest, Area) {
    Rectangle r(3.0, 4.0);
    EXPECT_EQ(r.area(), 12.0);
}

TEST(RectangleTest, Perimeter) {
    Rectangle r(3.0, 4.0);
    EXPECT_EQ(r.perimeter(), 14.0);
}

TEST(RectangleTest, ToString) {
    Rectangle r(3.0, 4.0);
    EXPECT_EQ(r.toString(), "Rectangle (3 4)");
}

TEST(RectangleTest, ToStringNonInteger) {
    Rectangle r(3.5, 4.2);
    EXPECT_EQ(r.toString(), "Rectangle (3.5 4.2)");
}

TEST(RectangleTest, ConstructorInvalidLengthThrows) {
    try {
        Rectangle r(0.0, 4.0);
        FAIL() << "Should throw std::string";
    } catch (const std::string& e) {
        EXPECT_EQ(e, "It's not a rectangle!");
    } catch (...) {
        FAIL() << "Should throw std::string";
    }
}

TEST(RectangleTest, ConstructorInvalidWidthThrows) {
    try {
        Rectangle r(3.0, -1.0);
        FAIL() << "Should throw std::string";
    } catch (const std::string& e) {
        EXPECT_EQ(e, "It's not a rectangle!");
    } catch (...) {
        FAIL() << "Should throw std::string";
    }
}
