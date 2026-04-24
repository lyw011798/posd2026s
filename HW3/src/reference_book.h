#ifndef REFERENCE_BOOK_H
#define REFERENCE_BOOK_H

#include <string>

#include "library_item.h"

class ReferenceBook : public LibraryItem {
public:
    ReferenceBook(long id, std::string title, std::string author);
    
    std::string get_type() override;
    std::string to_string() override;
};

#endif // REFERENCE_BOOK_H
