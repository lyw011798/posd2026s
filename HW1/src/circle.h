#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include "shape_visitor.h"

class Circle : public Shape {
public:
    Circle(double radius);
    double area() const override;
    double perimeter() const override;
    std::string toString() const override;
    void accept(ShapeVisitor* visitor) override;
private:
    double radius_;
};

#endif
