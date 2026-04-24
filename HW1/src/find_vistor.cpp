#include "find_vistor.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include "compound_shape.h"

FindVisitor::FindVisitor(std::function<bool(const Shape&)> predicate) 
    : predicate_(predicate) {}

void FindVisitor::visitCircle(Circle* circle) {
    if (predicate_(*circle)) {
        results_.push_back(circle);
    }
}

void FindVisitor::visitRectangle(Rectangle* rectangle) {
    if(predicate_(*rectangle)) {
        results_.push_back(rectangle);
    }
}

void FindVisitor::visitTriangle(Triangle* triangle) {
    if(predicate_(*triangle)) {
        results_.push_back(triangle);
    }
}

void FindVisitor::visitCompoundShape(CompoundShape* compound) {
    if(predicate_(*compound)){
        results_.push_back(compound);
    }
}

std::vector<Shape*> FindVisitor::getResults() const {
    return results_;
}