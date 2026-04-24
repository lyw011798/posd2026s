#ifndef NO_FINE_STRATEGY_H
#define NO_FINE_STRATEGY_H

#include <string>

#include "fine_strategy.h"

class NoFineStrategy : public FineStrategy {
public:
    double calculate_fine(LibraryItem* item, int days_overdue) const override;
    std::string name() const override;
};

#endif // NO_FINE_STRATEGY_H
