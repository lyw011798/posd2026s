#include "compound_shape.h"

double CompoundShape::area() const {
    double totalArea = 0;
    for (const auto& shape : shapes_) {
        totalArea += shape->area();
    }
    return totalArea;
}

double CompoundShape::perimeter() const {
    double totalPerimeter = 0;
    for (const auto& shape : shapes_) {
        totalPerimeter += shape->perimeter();
    }
    return totalPerimeter;
}


void CompoundShape::add(std::unique_ptr<Shape> shape) {
    shapes_.push_back(std::move(shape));
}

void CompoundShape::accept(ShapeVisitor* visitor) {
    visitor->visitCompoundShape(this);
    for (const auto& shape : shapes_) {
        shape->accept(visitor);
    }
}

std::vector<const Shape*> CompoundShape::find(std::function<bool(const Shape&)> predicate) const {
    std::vector<const Shape*> result;
    if (predicate(*this)) {
        result.push_back(this);
    }
    for (const auto& shape : shapes_) {
        std::vector<const Shape*> sub_result = shape->find(predicate);
        result.insert(result.end(), sub_result.begin(), sub_result.end());
    }
    return result;
}

CompoundShape::Iterator CompoundShape::begin() {
    return shapes_.begin();
}

CompoundShape::Iterator CompoundShape::end() {
    return shapes_.end();
}

CompoundShape::ConstIterator CompoundShape::begin() const {
    return shapes_.begin();
}

CompoundShape::ConstIterator CompoundShape::end() const {
    return shapes_.end();
}