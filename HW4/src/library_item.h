#ifndef LIBRARY_ITEM_H
#define LIBRARY_ITEM_H

#include <string>
#include <stdexcept>

class Iterator;
class LibraryItemVisitor;

class LibraryItem {
public:
    LibraryItem(long id, std::string title, std::string author);

    virtual ~LibraryItem() = default;

    long get_id();
    std::string get_title();
    std::string get_author();

    virtual std::string get_type() = 0;
    virtual std::string to_string() = 0;
    virtual void add_item(LibraryItem* item);
    virtual Iterator* create_iterator();
    virtual void accept(LibraryItemVisitor& visitor) = 0;
protected:
    long id_;
    std::string title_;
    std::string author_;
};

#endif // LIBRARY_ITEM_H
