#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>
#include <functional>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string toString() const = 0;
    virtual void accept(class ShapeVisitor* visitor) {};

    virtual std::vector<const Shape*> find(std::function<bool(const Shape&)> predicate) const {
        std::vector<const Shape*> result;
        if (predicate(*this)) {
            result.push_back(this);
        }
        return result;
    }
};

#endif
