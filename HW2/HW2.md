# Object-Oriented Programming 2026 Spring Assignment

## Assignment 2

### Purpose of this assignment:
Let students practice **inheritance**, **polymorphism**, and the **Strategy design pattern** in C++20.

### Background:
In this assignment, you will build a `LibraryManagementSystem` that manages different types of library items. Beyond storing and searching items, the system must be able to calculate overdue fines using interchangeable fine strategies — a direct application of the **Strategy pattern**.

### Problems:
Please implement and test the following classes and methods:

#### Base Class `LibraryItem`:
- **Constructor**: `LibraryItem(long id, std::string title, std::string author)`
- **Methods**:
  - `get_id()` - Returns the ID of the item
  - `get_title()` - Returns the title of the item
  - `get_author()` - Returns the author of the item
  - `get_type()` - Returns the type of item (pure virtual)
  - `to_string()` - Returns string representation of the item (pure virtual)

#### Derived Class `Book`:
- **Constructor**: `Book(long id, std::string title, std::string author)`
- **Methods**:
  - `get_type()` - Returns `"Book"`
  - `to_string()` - Returns `"Book: {title} by {author}"`

#### Derived Class `ReferenceBook`:
- **Constructor**: `ReferenceBook(long id, std::string title, std::string author)`
- **Methods**:
  - `get_type()` - Returns `"ReferenceBook"`
  - `to_string()` - Returns `"ReferenceBook: {title} by {author}"`

#### Derived Class `EBook`:
- **Constructor**: `EBook(long id, std::string title, std::string author)`
- **Methods**:
  - `get_type()` - Returns `"EBook"`
  - `to_string()` - Returns `"EBook: {title} by {author}"`

#### Abstract Class `FineStrategy`:
- **Methods**:
  - `calculate_fine(LibraryItem* item, int days_overdue)` - Returns the fine amount as `double` (pure virtual). Must return `0.0` when `days_overdue <= 0`.
  - `name()` - Returns the strategy name as `std::string` (pure virtual)

#### Concrete Strategy `StandardFineStrategy`:
- Inherits from `FineStrategy`
- Applies a **flat daily rate** based on item type:
  | Type | Rate per day |
  |---|---|
  | `Book` | $1.0 |
  | `ReferenceBook` | $2.0 |
  | `EBook` | $0.5 |
- **Methods**:
  - `calculate_fine(LibraryItem* item, int days_overdue)` - Returns `base_rate * days_overdue`
  - `name()` - Returns `"StandardFineStrategy"`

#### Concrete Strategy `ProgressiveFineStrategy`:
- Inherits from `FineStrategy`
- Uses the **same base rates** as `StandardFineStrategy`, but the rate **doubles** for every day beyond the first 7 days overdue:
  - `days_overdue <= 7` : `base_rate * days_overdue`
  - `days_overdue >  7` : `base_rate * 7 + base_rate * 2.0 * (days_overdue - 7)`
- **Methods**:
  - `calculate_fine(LibraryItem* item, int days_overdue)` - Returns fine using the progressive formula
  - `name()` - Returns `"ProgressiveFineStrategy"`

#### Concrete Strategy `NoFineStrategy`:
- Inherits from `FineStrategy`
- Always returns `0.0` regardless of item type or overdue days (used for grace periods or special events)
- **Methods**:
  - `calculate_fine(LibraryItem* item, int days_overdue)` - Always returns `0.0`
  - `name()` - Returns `"NoFineStrategy"`

#### `LibraryManagementSystem` Class:
- **Methods**:
  - `add_item(LibraryItem* item)` - Adds an item to the library
  - `get_all_items()` - Returns `std::vector<LibraryItem*>` of all items in insertion order
  - `search_by_title(std::string title)` - Returns `std::vector<LibraryItem*>` of items matching the title
  - `search_by_author(std::string author)` - Returns `std::vector<LibraryItem*>` of items by the author
  - `get_total_items()` - Returns the total number of items
  - `set_fine_strategy(FineStrategy* strategy)` - Sets the fine calculation strategy
  - `calculate_fine(LibraryItem* item, int days_overdue)` - Calculates fine using the current strategy. Returns `0.0` if no strategy is set.

(For these methods, you have to write at least one test for yourself.)

Please follow the declaration and write the implementation in the corresponding `.cpp` files.

### Class Declaration
**Please download the files in the `template_code` folder and follow the repository structure to put the files in your repository.**
**The sample code only contains public class declarations. You can add the private members and methods as required according to the requirement.**

### Repository Structure
```
. (posd2026s_{student ID}_hw)
├── .gitignore (provided by TA)
├── CMakeLists.txt (provided by TA)
├── src/
│   ├── library_item.h (provided by TA)
│   ├── library_item.cpp
│   ├── book.h (provided by TA)
│   ├── book.cpp
│   ├── reference_book.h (provided by TA)
│   ├── reference_book.cpp
│   ├── ebook.h (provided by TA)
│   ├── ebook.cpp
│   ├── fine_strategy.h (provided by TA)
│   ├── standard_fine_strategy.h (provided by TA)
│   ├── standard_fine_strategy.cpp
│   ├── progressive_fine_strategy.h (provided by TA)
│   ├── progressive_fine_strategy.cpp
│   ├── no_fine_strategy.h (provided by TA)
│   ├── no_fine_strategy.cpp
│   ├── library_management_system.h (provided by TA)
│   └── library_management_system.cpp
└── tests/
    ├── ut_book.cpp
    ├── ut_ebook.cpp
    ├── ut_library_item.cpp
    ├── ut_library.cpp
    ├── ut_reference_book.cpp
    └── ut_fine_strategy.cpp
```

### Commands to Execute the Program

```bash
$ cd build
$ cmake ..
$ make
$ ./unit_tests
```

### Score

1. Implementation and tests by yourself (45%)
    1. Implementation and tests of `LibraryItem`, `Book`, `ReferenceBook`, `EBook` (5%)
    2. Implementation and tests of `LibraryManagementSystem` basic operations (10%)
    3. Implementation and tests of `StandardFineStrategy` (10%)
    4. Implementation and tests of `ProgressiveFineStrategy` (10%)
    5. Implementation and tests of `NoFineStrategy` and strategy switching (10%)
2. Tests by TA (45%)
    1. Tests of `LibraryItem` inheritance and polymorphism (5%)
    2. Tests of `LibraryManagementSystem` operations (10%)
    3. Tests of `StandardFineStrategy` correctness for all item types (10%)
    4. Tests of `ProgressiveFineStrategy` (boundary at 7 days, all item types) (10%)
    5. Tests of `NoFineStrategy` and runtime strategy switching (10%)
3. Implementation of strategy pattern (10%)

Total: 100%

### Notes
1. Please implement your test cases reasonably; otherwise, you will get no points for that sub-problem.
3. TA will use the `_TA` project in Jenkins to test your program.
4. `calculate_fine` on `LibraryManagementSystem` must return `0.0` when no strategy has been set.
5. The `ProgressiveFineStrategy` threshold is exactly **7 days** — `days_overdue == 7` still uses the flat rate.
