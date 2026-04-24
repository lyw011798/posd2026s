#include "fine_calculation_visitor.h"
#include "book.h"
#include "ebook.h"
#include "reference_book.h"
#include "book_bundle.h"
#include "book_bundle_iterator.h"

FineCalculationVisitor::FineCalculationVisitor(int days_overdue)
    : _days_overdue(days_overdue), _total_fine(0.0) {}

void FineCalculationVisitor::visit_book(Book& book) {
    if (_days_overdue > 0) {
        _total_fine += 1.0 * _days_overdue;
    }
}

void FineCalculationVisitor::visit_ebook(EBook& ebook) {
    if (_days_overdue > 0) {
        _total_fine += 0.5 * _days_overdue;
    }
}

void FineCalculationVisitor::visit_reference_book(ReferenceBook& reference_book) {
    if (_days_overdue > 0) {
        _total_fine += 2.0 * _days_overdue;
    }
}

void FineCalculationVisitor::visit_book_bundle(BookBundle& book_bundle) {
    Iterator* it = book_bundle.create_iterator();
    while (!it->is_done()) {
        LibraryItem* item = it->current_item();
        item->accept(*this);
        it->next();
    }
    delete it;
}

double FineCalculationVisitor::get_total_fine() const {
    return _total_fine;
}
