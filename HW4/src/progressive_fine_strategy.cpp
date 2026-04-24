#include "progressive_fine_strategy.h"
#include "book_bundle.h"

double ProgressiveFineStrategy::calculate_fine(LibraryItem* item, int days_overdue) const {
    if (days_overdue <= 0) {
        return 0.0;
    }

    if (item->get_type() == "BookBundle") {
        auto bundle = dynamic_cast<BookBundle*>(item);
        double total_fine = 0.0;
        if (bundle) {
            for (auto child : bundle->get_items()) {
                total_fine += calculate_fine(child, days_overdue);
            }
        }
        return total_fine;
    }

    double base_rate = get_base_rate(item->get_type());
    
    if (days_overdue <= 7) {
        return base_rate * days_overdue;
    } else {
        return (base_rate * 7) + (base_rate * 2.0 * (days_overdue - 7));
    }
}

std::string ProgressiveFineStrategy::name() const {
    return "ProgressiveFineStrategy";
}
