#include "sorter.h"

Sorter::Sorter(std::unique_ptr<SortStrategy> strategy) : strategy_(std::move(strategy)) {}

void Sorter::sort(std::vector<Shape*>& shapes) {
    strategy_->sort(shapes);
}