#pragma once

#include "shape.h"
#include "sortstrategy.h"
#include <vector>
#include <memory>
#include <algorithm>

class Sorter {
public:
    Sorter(std::unique_ptr<SortStrategy> strategy);
    void sort(std::vector<Shape*>& shapes);

private:
    std::unique_ptr<SortStrategy> strategy_;
};
