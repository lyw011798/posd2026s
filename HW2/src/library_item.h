#ifndef LIBRARY_ITEM_H
#define LIBRARY_ITEM_H

#include <string>

class LibraryItem {
public:
    LibraryItem(long id, std::string title, std::string author);
    
    virtual ~LibraryItem() = default;
    
    long get_id();
    std::string get_title();
    std::string get_author();
    
    virtual std::string get_type() = 0;
    virtual std::string to_string() = 0;

private:
    long id_;
    std::string title_;
    std::string author_;
};

#endif // LIBRARY_ITEM_H
