#ifndef STANDARD_FINE_STRATEGY_H
#define STANDARD_FINE_STRATEGY_H

#include <string>

#include "fine_strategy.h"

class StandardFineStrategy : public FineStrategy {
public:
    double calculate_fine(LibraryItem* item, int days_overdue) const override;
    std::string name() const override;
};

#endif // STANDARD_FINE_STRATEGY_H
