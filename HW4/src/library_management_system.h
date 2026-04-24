#ifndef LIBRARY_MANAGEMENT_SYSTEM_H
#define LIBRARY_MANAGEMENT_SYSTEM_H

#include <vector>
#include <string>

#include "library_item.h"
#include "fine_strategy.h"

class LibraryManagementSystem {
public:
    LibraryManagementSystem();

    void add_item(LibraryItem* item);

    std::vector<LibraryItem*> get_all_items();

    std::vector<LibraryItem*> search_by_title(std::string title);
    std::vector<LibraryItem*> search_by_author(std::string author);

    int get_total_items();

    void set_fine_strategy(FineStrategy* strategy);

    double calculate_fine(LibraryItem* item, int days_overdue);

private:
    std::vector<LibraryItem*> items_;
    FineStrategy* strategy_ = nullptr;
};

#endif // LIBRARY_MANAGEMENT_SYSTEM_H
