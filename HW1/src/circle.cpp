#include "circle.h"
#include <cmath>
#include <sstream>

Circle::Circle(double radius) : radius_(radius) {
    if (radius <= 0) {
        throw std::string("It's not a circle!");
    }
}

double Circle::area() const {
    return M_PI * radius_ * radius_;
}

double Circle::perimeter() const {
    return 2 * M_PI * radius_;
}

std::string Circle::toString() const {
    std::stringstream ss;
    ss << "Circle (" << radius_ << ")";
    return ss.str();
}

void Circle::accept(ShapeVisitor* visitor) {
    visitor->visitCircle(this);
}