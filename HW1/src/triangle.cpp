#include "triangle.h"
#include <cmath>
#include <sstream>
#include "find_vistor.h"

Triangle::Triangle(double a, double b, double c) : a_(a), b_(b), c_(c) {
    if (a <= 0 || b <= 0 || c <= 0 || (a + b <= c) || (a + c <= b) || (b + c <= a)) {
        throw std::string("It's not a triangle!");
    }
}

double Triangle::area() const {
    double s = (a_ + b_ + c_) / 2.0;
    return std::sqrt(s * (s - a_) * (s - b_) * (s - c_));
}

double Triangle::perimeter() const {
    return a_ + b_ + c_;
}

std::string Triangle::toString() const {
    std::stringstream ss;
    ss << "Triangle (" << a_ << " " << b_ << " " << c_ << ")";
    return ss.str();
}

void Triangle::accept(ShapeVisitor* vistor) {
    vistor->visitTriangle(this);
}
