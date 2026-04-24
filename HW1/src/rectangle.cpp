#include "rectangle.h"
#include <sstream>
#include "shape_visitor.h"

Rectangle::Rectangle(double length, double width) : length_(length), width_(width) {
    if (length <= 0 || width <= 0) {
        throw std::string("It's not a rectangle!");
    }
}

double Rectangle::area() const {
    return length_ * width_;
}

double Rectangle::perimeter() const {
    return 2 * (length_ + width_);
}

std::string Rectangle::toString() const {
    std::stringstream ss;
    ss << "Rectangle (" << length_ << " " << width_ << ")";
    return ss.str();
}

void Rectangle::accept(ShapeVisitor* vistor) {
    vistor -> visitRectangle(this);
}