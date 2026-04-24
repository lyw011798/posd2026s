#pragma once

#include "shape.h"
#include <vector>
#include <memory>
#include <algorithm>

class SortStrategy {
public:
    virtual ~SortStrategy() = default;
    virtual void sort(std::vector<Shape*>& shapes) = 0;
};

class AreaIncreasingStrategy : public SortStrategy {
public:
    void sort(std::vector<Shape*>& shapes) override;
};

class AreaDecreasingStrategy : public SortStrategy {
public:
    void sort(std::vector<Shape*>& shapes) override;
};

class PerimeterIncreasingStrategy : public SortStrategy {
public:
    void sort(std::vector<Shape*>& shapes) override;
};

class PerimeterDecreasingStrategy : public SortStrategy {
public:
    void sort(std::vector<Shape*>& shapes) override;
};