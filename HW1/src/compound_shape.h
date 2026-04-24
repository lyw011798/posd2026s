#pragma once

#include "shape.h"
#include "shape_visitor.h"
#include <vector>
#include <memory>

class CompoundShape : public Shape {
public:
    using Iterator = std::vector<std::unique_ptr<Shape>>::iterator;
    using ConstIterator = std::vector<std::unique_ptr<Shape>>::const_iterator;

    double area() const override;
    double perimeter() const override;
    void accept(ShapeVisitor* visitor) override;
    
    std::vector<const Shape*> find(std::function<bool(const Shape&)> predicate) const override;

    void add(std::unique_ptr<Shape> shape);
    
    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;

private:
    std::vector<std::unique_ptr<Shape>> shapes_;
};