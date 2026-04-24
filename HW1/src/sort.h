#ifndef SORT_H
#define SORT_H

#include "shape.h"
#include <algorithm>
#include <string>
#include <vector>

class Sort {
public:
    struct ByAreaAscending {
        bool operator()(Shape* a, Shape* b) const {
            return a->area() < b->area();
        }
    };

    struct ByAreaDescending {
        bool operator()(Shape* a, Shape* b) const {
            return a->area() > b->area();
        }
    };

    struct ByPerimeterAscending {
        bool operator()(Shape* a, Shape* b) const {
            return a->perimeter() < b->perimeter();
        }
    };

    struct ByPerimeterDescending {
        bool operator()(Shape* a, Shape* b) const {
            return a->perimeter() > b->perimeter();
        }
    };

    static void sortShapes(std::vector<Shape*>& shapes,
                           const std::string& sortBy,
                           const std::string& order) {
        if (sortBy == "area" && order == "inc") {
            std::sort(shapes.begin(), shapes.end(), ByAreaAscending());
        } else if (sortBy == "area" && order == "dec") {
            std::sort(shapes.begin(), shapes.end(), ByAreaDescending());
        } else if (sortBy == "perimeter" && order == "inc") {
            std::sort(shapes.begin(), shapes.end(), ByPerimeterAscending());
        } else if (sortBy == "perimeter" && order == "dec") {
            std::sort(shapes.begin(), shapes.end(), ByPerimeterDescending());
        }
        // empty/invalid: no-op, shapes stay in original order
    }
};

#endif
