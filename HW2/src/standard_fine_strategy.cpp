#include "standard_fine_strategy.h"

double StandardFineStrategy::calculate_fine(LibraryItem* item, int days_overdue) const {
    if (days_overdue <= 0) {
        return 0.0;
    }

    double rate = get_base_rate(item->get_type());
    return rate * days_overdue;
}

std::string StandardFineStrategy::name() const {
    return "StandardFineStrategy";
}
