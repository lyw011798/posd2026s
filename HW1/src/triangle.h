#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

class Triangle : public Shape {
public:
    Triangle(double a, double b, double c);
    double area() const override;
    double perimeter() const override;
    std::string toString() const override;
    void accept(ShapeVisitor* visitor) override;
    
private:
    double a_, b_, c_;
};

#endif
