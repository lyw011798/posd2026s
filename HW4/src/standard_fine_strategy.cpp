#include "standard_fine_strategy.h"
#include "book_bundle.h"

double StandardFineStrategy::calculate_fine(LibraryItem* item, int days_overdue) const {
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

    double rate = get_base_rate(item->get_type());
    return rate * days_overdue;
}

std::string StandardFineStrategy::name() const {
    return "StandardFineStrategy";
}
