#ifndef FINE_STRATEGY_H
#define FINE_STRATEGY_H

#include <string>
#include <unordered_map>

#include "library_item.h"

class FineStrategy {
public:
    virtual ~FineStrategy() = default;

    virtual double calculate_fine(LibraryItem* item, int days_overdue) const = 0;
    virtual std::string name() const = 0;

protected:
    static double get_base_rate(const std::string& type) {
        static const std::unordered_map<std::string, double> rate_map = {
            {"Book", 1.0},
            {"ReferenceBook", 2.0},
            {"EBook", 0.5}
        };
        auto it = rate_map.find(type);
        return (it != rate_map.end()) ? it->second : 0.0;
    }
};

#endif // FINE_STRATEGY_H

