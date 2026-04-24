#include "library_management_system.h"

LibraryManagementSystem::LibraryManagementSystem() : strategy_(nullptr) {}

void LibraryManagementSystem::add_item(LibraryItem* item) {
    items_.push_back(item);
}

std::vector<LibraryItem*> LibraryManagementSystem::get_all_items() {
    return items_;
}

int LibraryManagementSystem::get_total_items() {
    return items_.size();
}

std::vector<LibraryItem*> LibraryManagementSystem::search_by_title(std::string title) {
    std::vector<LibraryItem*> result;
    for (auto item : items_) {
        if (item->get_title() == title) {
            result.push_back(item);
        }
    }
    return result;
}

std::vector<LibraryItem*> LibraryManagementSystem::search_by_author(std::string author) {
    std::vector<LibraryItem*> result;
    for (auto item : items_) {
        if (item->get_author() == author) {
            result.push_back(item);
        }
    }
    return result;
}

void LibraryManagementSystem::set_fine_strategy(FineStrategy* strategy) {
    strategy_ = strategy;
}

double LibraryManagementSystem::calculate_fine(LibraryItem* item, int days_overdue) {
    if (strategy_ == nullptr) {
        return 0.0;
    }
    return strategy_->calculate_fine(item, days_overdue);
}
