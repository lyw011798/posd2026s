#ifndef EBOOK_H
#define EBOOK_H

#include <string>

#include "library_item.h"

class EBook : public LibraryItem {
public:
    EBook(long id, std::string title, std::string author);
    
    std::string get_type() override;
    std::string to_string() override;
};

#endif // EBOOK_H
