#ifndef BOOK_BUNDLE_H
#define BOOK_BUNDLE_H

#include "library_item.h"
#include <vector>
#include <string>

class BookBundle : public LibraryItem {
public:
    BookBundle(long id, std::string title);
    
    // Override pure virtual methods
    std::string get_type() override;
    std::string to_string() override;

    // Composite management methods
    void add_item(LibraryItem* item) override;
    Iterator* create_iterator() override;
    void accept(LibraryItemVisitor& visitor) override;

    // Access children for fine calculation
    const std::vector<LibraryItem*>& get_items() const;

private:
    std::vector<LibraryItem*> _items;
};

#endif // BOOK_BUNDLE_H
