#pragma once
#include "shape.h"
#include "triangle.h"
#include "circle.h"
#include "rectangle.h"
#include "convex_polygon.h"
#include <memory>

class ShapeFactory {
public:
    static std::unique_ptr<Shape> createTriangle(double a, double b, double c) {
        if (a + b <= c || a + c <= b || b + c <= a) {
            return nullptr;
        }
        return std::unique_ptr<Shape>(new Triangle(a, b, c));
    }

    static std::unique_ptr<Shape> createCircle(double radius) {
        if (radius < 0 ) {
            return nullptr;
        }
        return std::unique_ptr<Shape>(new Circle(radius));
    }

    static std::unique_ptr<Shape> createRect(double length, double width) {
        if (length < 0 || width < 0 ) {
            return nullptr;
        }
        return std::unique_ptr<Shape>(new Rectangle(length, width));
    }

    
};
