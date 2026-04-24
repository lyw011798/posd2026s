#pragma once

class Circle;
class Rectangle;
class Triangle;
class CompoundShape;

class ShapeVisitor {
public:
    virtual ~ShapeVisitor() = default;
    virtual void visitCircle(Circle* circle) = 0;
    virtual void visitRectangle(Rectangle* rectangle) = 0;
    virtual void visitTriangle(Triangle* triangle) = 0;
    virtual void visitCompoundShape(CompoundShape* compound) = 0;
};
