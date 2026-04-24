#include "no_fine_strategy.h"

double NoFineStrategy::calculate_fine(LibraryItem* item, int days_overdue) const {
    return 0.0;
}

std::string NoFineStrategy::name() const {
    return "NoFineStrategy";
}
