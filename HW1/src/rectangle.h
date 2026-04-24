#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape {
public:
    Rectangle(double length, double width);
    double area() const override;
    double perimeter() const override;
    std::string toString() const override;
    void accept(ShapeVisitor* visitor) override;

private:
    double length_, width_;
};

#endif
