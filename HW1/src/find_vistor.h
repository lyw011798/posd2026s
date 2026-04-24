#pragma once

#include "shape_visitor.h"
#include "shape.h"
#include <vector>
#include <functional>

class FindVisitor : public ShapeVisitor {
public:
    explicit FindVisitor(std::function<bool(const Shape&)> predicate);
    
    void visitCircle(Circle* circle) override;
    void visitRectangle(Rectangle* rectangle) override;
    void visitTriangle(Triangle* triangle) override;
    void visitCompoundShape(CompoundShape* compound) override;
    
    std::vector<Shape*> getResults() const;

private:
    std::function<bool(const Shape&)> predicate_;
    std::vector<Shape*> results_;
};
