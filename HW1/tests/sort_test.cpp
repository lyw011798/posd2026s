#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"
#include "sort.h"

class SortTest : public ::testing::Test {
protected:
    // Circle areas: 78.5, 28.3, 12.6  (r=5, r=3, r=2)
    // Triangle areas: 6 (3,4,5)
    // Rectangle area: 6 (2,3)
    std::vector<Shape*> shapes;

    void SetUp() override {
        shapes = {
            new Circle(5.0),      // area=78.5, perim=31.4
            new Rectangle(2.0, 3.0), // area=6,    perim=10
            new Triangle(3.0, 4.0, 5.0), // area=6, perim=12
            new Circle(3.0),      // area=28.3, perim=18.8
        };
    }

    void TearDown() override {
        for (Shape* s : shapes) delete s;
    }
};

TEST_F(SortTest, SortByAreaAscending) {
    Sort::sortShapes(shapes, "area", "inc");
    // Expected order by area ascending: Rectangle(6), Triangle(6), Circle(3), Circle(5)
    // Rectangle and Triangle both have area 6 — relative order between them is stable-ish,
    // but we check the endpoints.
    EXPECT_NEAR(shapes.front()->area(), 6.0, 0.001);
    EXPECT_NEAR(shapes.back()->area(), M_PI * 25.0, 0.001); // Circle(5)
}

TEST_F(SortTest, SortByAreaDescending) {
    Sort::sortShapes(shapes, "area", "dec");
    EXPECT_NEAR(shapes.front()->area(), M_PI * 25.0, 0.001); // Circle(5) largest
    EXPECT_NEAR(shapes.back()->area(), 6.0, 0.001);
}

TEST_F(SortTest, SortByPerimeterAscending) {
    Sort::sortShapes(shapes, "perimeter", "inc");
    // Perimeters: Rectangle=10, Circle(3)=18.8, Triangle=12, Circle(5)=31.4
    // Ascending: Rectangle(10), Triangle(12), Circle(3)(18.8), Circle(5)(31.4)
    EXPECT_NEAR(shapes.front()->perimeter(), 10.0, 0.001);
    EXPECT_NEAR(shapes.back()->perimeter(), 2.0 * M_PI * 5.0, 0.001);
}

TEST_F(SortTest, SortByPerimeterDescending) {
    Sort::sortShapes(shapes, "perimeter", "dec");
    EXPECT_NEAR(shapes.front()->perimeter(), 2.0 * M_PI * 5.0, 0.001); // Circle(5) largest
    EXPECT_NEAR(shapes.back()->perimeter(), 10.0, 0.001); // Rectangle smallest
}

TEST_F(SortTest, NoSortWhenCriteriaEmpty) {
    // Store the original first shape pointer to verify order unchanged
    Shape* originalFirst = shapes[0];
    Sort::sortShapes(shapes, "", "");
    EXPECT_EQ(shapes[0], originalFirst);
}
