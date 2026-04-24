#include "sortstrategy.h"

void AreaIncreasingStrategy::sort(std::vector<Shape*>& shapes) {
    std::sort(shapes.begin(), shapes.end(), [](const Shape* a, const Shape* b) {
        return a->area() < b->area();
    });
}

void AreaDecreasingStrategy::sort(std::vector<Shape*>& shapes) {
    std::sort(shapes.begin(), shapes.end(), [](const Shape* a, const Shape* b) {
        return a->area() > b->area();
    });
}

void PerimeterIncreasingStrategy::sort(std::vector<Shape*>& shapes) {
    std::sort(shapes.begin(), shapes.end(), [](const Shape* a, const Shape* b) {
        return a->perimeter() < b->perimeter();
    });
}

void PerimeterDecreasingStrategy::sort(std::vector<Shape*>& shapes) {
    std::sort(shapes.begin(), shapes.end(), [](const Shape* a, const Shape* b) {
        return a->perimeter() > b->perimeter();
    });
}