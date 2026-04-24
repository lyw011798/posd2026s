#ifndef FINE_CALCULATION_VISITOR_H
#define FINE_CALCULATION_VISITOR_H

#include "library_item_visitor.h"

class FineCalculationVisitor : public LibraryItemVisitor {
public:
    FineCalculationVisitor(int days_overdue);

    void visit_book(Book& book) override;
    void visit_ebook(EBook& ebook) override;
    void visit_reference_book(ReferenceBook& reference_book) override;
    void visit_book_bundle(BookBundle& book_bundle) override;

    double get_total_fine() const;

private:
    int _days_overdue;
    double _total_fine;
};

#endif // FINE_CALCULATION_VISITOR_H
