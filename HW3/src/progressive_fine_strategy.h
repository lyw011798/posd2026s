#ifndef PROGRESSIVE_FINE_STRATEGY_H
#define PROGRESSIVE_FINE_STRATEGY_H

#include <string>

#include "fine_strategy.h"

class ProgressiveFineStrategy : public FineStrategy {
public:
    double calculate_fine(LibraryItem* item, int days_overdue) const override;
    std::string name() const override;
};

#endif // PROGRESSIVE_FINE_STRATEGY_H
