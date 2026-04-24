# Pattern-Oriented Software Design 2026 Spring Assignment

## Assignment 4

### Purpose of this assignment:
Let students practice the **Iterator** and **Visitor** design patterns in C++20.

### Background:
In this assignment, you will extend the `LibraryManagementSystem` by introducing two new patterns:

1. **Iterator Pattern**: Provide a uniform way to traverse the children of a `BookBundle` (composite). Leaf nodes (`Book`, `EBook`, `ReferenceBook`) return a `NullIterator` that is immediately done, while `BookBundle` returns a `BookBundleIterator` that iterates over its direct children.

2. **Visitor Pattern**: Provide a way to define new operations on the `LibraryItem` hierarchy without modifying the existing classes. Each `LibraryItem` subclass implements an `accept()` method that dispatches to the appropriate visitor method, enabling **double dispatch**.

---

### Problems:

#### Part 1: Iterator Pattern

Please implement and test the following classes and methods:

##### Abstract Class `Iterator`:
- **Header**: `iterator.h` (provided by TA)
- **Methods** (all pure virtual):
  - `void first()` - Resets the iterator to the first element.
  - `void next()` - Advances to the next element.
  - `bool is_done() const` - Returns `true` if there are no more elements.
  - `LibraryItem* current_item() const` - Returns the current element.

##### Class `NullIterator`:
- **Header**: `null_iterator.h` (provided by TA)
- Inherits from `Iterator`
- Represents an iterator for leaf nodes that have no children.
- **Behavior**:
  - `first()` - Does nothing.
  - `next()` - Throws `std::runtime_error("No next item in NullIterator")`.
  - `is_done()` - Always returns `true`.
  - `current_item()` - Throws `std::runtime_error("No current item in NullIterator")`.

##### Class `BookBundleIterator`:
- **Header**: `book_bundle_iterator.h` (provided by TA)
- Inherits from `Iterator`
- Iterates over the **direct children** of a `BookBundle`.
- **Constructor**: `BookBundleIterator(const std::vector<LibraryItem*>& items)`
- **Behavior**:
  - `first()` - Resets the index to 0.
  - `next()` - Advances to the next child. Throws `std::runtime_error("No next item in BookBundleIterator")` if already done.
  - `is_done()` - Returns `true` if the index has passed the last child.
  - `current_item()` - Returns the child at the current index. Throws `std::runtime_error("No current item in BookBundleIterator")` if already done.

##### Factory Method `create_iterator()` on `LibraryItem`:
- `LibraryItem::create_iterator()` - Returns `new NullIterator()` by default (for leaf nodes). Implement in `library_item.cpp`.
- `BookBundle::create_iterator()` - Returns `new BookBundleIterator(_items)`. Implement in `book_bundle.cpp`.

---

#### Part 2: Visitor Pattern

Please implement and test the following classes and methods:

##### Abstract Class `LibraryItemVisitor`:
- **Header**: `library_item_visitor.h` (provided by TA)
- **Methods** (all pure virtual):
  - `void visit_book(Book& book)`
  - `void visit_ebook(EBook& ebook)`
  - `void visit_reference_book(ReferenceBook& reference_book)`
  - `void visit_book_bundle(BookBundle& book_bundle)`

##### Method `accept()` on `LibraryItem`:
- `LibraryItem` declares `virtual void accept(LibraryItemVisitor& visitor) = 0` (pure virtual, provided by TA).
- Each concrete class must implement `accept()` in the corresponding `.cpp` file by calling the matching visitor method:
  - `Book::accept` calls `visitor.visit_book(*this)`
  - `EBook::accept` calls `visitor.visit_ebook(*this)`
  - `ReferenceBook::accept` calls `visitor.visit_reference_book(*this)`
  - `BookBundle::accept` calls `visitor.visit_book_bundle(*this)`

##### Concrete Visitor: `ItemCountVisitor`
- **Header**: `item_count_visitor.h` (provided by TA)
- **Implementation**: `item_count_visitor.cpp` (implement yourself)
- Inherits from `LibraryItemVisitor`
- Traverses the `LibraryItem` hierarchy and counts items by type.
- **Behavior**:
  - `visit_book(Book&)` - Increments book count.
  - `visit_ebook(EBook&)` - Increments ebook count.
  - `visit_reference_book(ReferenceBook&)` - Increments reference book count.
  - `visit_book_bundle(BookBundle&)` - Increments bundle count, then recursively calls `accept(*this)` on each child in the bundle.
- **Getter methods**:
  - `int get_book_count() const`
  - `int get_ebook_count() const`
  - `int get_reference_book_count() const`
  - `int get_bundle_count() const`
  - `int get_total_count() const` - Returns the sum of book, ebook, and reference book counts (excludes bundles).

##### Concrete Visitor: `FineCalculationVisitor`
- **Header**: `fine_calculation_visitor.h` (provided by TA)
- **Implementation**: `fine_calculation_visitor.cpp` (implement yourself)
- Inherits from `LibraryItemVisitor`
- Calculates the total fine using **double dispatch** instead of `dynamic_cast`.
- **Constructor**: `FineCalculationVisitor(int days_overdue)`
- **Behavior** (flat-rate only):
  - `visit_book(Book&)` - Adds `1.0 * days_overdue` to total (if `days_overdue > 0`).
  - `visit_ebook(EBook&)` - Adds `0.5 * days_overdue` to total (if `days_overdue > 0`).
  - `visit_reference_book(ReferenceBook&)` - Adds `2.0 * days_overdue` to total (if `days_overdue > 0`).
  - `visit_book_bundle(BookBundle&)` - Recursively calls `accept(*this)` on each child in the bundle.
  - If `days_overdue <= 0`, the total fine is `0.0`.
- **Getter method**:
  - `double get_total_fine() const`

---

### Note:
- The Iterator pattern only iterates over **direct children**. It does not recursively flatten nested bundles.
- The Visitor pattern handles recursion inside the `visit(BookBundle&)` method by calling `accept()` on each child.
- All previous functionality (Composite, Strategy) must remain intact.

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
│   ├── book.h (provided by TA)
│   ├── book.cpp
│   ├── ebook.h (provided by TA)
│   ├── ebook.cpp
│   ├── reference_book.h (provided by TA)
│   ├── reference_book.cpp
│   ├── library_item.h (provided by TA)
│   ├── library_item.cpp
│   ├── book_bundle.h (provided by TA)
│   ├── book_bundle.cpp
│   ├── iterator.h (provided by TA)
│   ├── null_iterator.h (provided by TA)
│   ├── null_iterator.cpp
│   ├── book_bundle_iterator.h (provided by TA)
│   ├── book_bundle_iterator.cpp
│   ├── library_item_visitor.h (provided by TA)
│   ├── item_count_visitor.h (provided by TA)
│   ├── item_count_visitor.cpp
│   ├── fine_calculation_visitor.h (provided by TA)
│   ├── fine_calculation_visitor.cpp
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
    ├── ut_reference_book.cpp
    ├── ut_library_item.cpp
    ├── ut_book_bundle.cpp
    ├── ut_fine_strategy.cpp
    ├── ut_library.cpp
    ├── ut_iterator.cpp
    └── ut_visitor.cpp
```

### Commands to Execute the Program

```bash
$ cd build
$ cmake ..
$ make
$ ./unit_tests
```

### Score

1. Implementation and tests by yourself (40%)
    1. Implementation and tests of `create_iterator()` and Iterator traversal (10%)
    2. Implementation and tests of `accept()` on all `LibraryItem` subclasses (5%)
    3. Implementation and tests of `ItemCountVisitor` (15%)
    4. Implementation and tests of `FineCalculationVisitor` (10%)
2. Tests by TA (50%)
    1. Tests of `NullIterator` behavior (`next()`/`current_item()` throw, `is_done()` always true) (10%)
    2. Tests of `BookBundleIterator` behavior (traversal, `first()` reset, boundary throws) (10%)
    3. Tests of `ItemCountVisitor` (flat bundle, nested bundle, empty bundle, polymorphic) (15%)
    4. Tests of `FineCalculationVisitor` (single items, bundles, nested bundles, edge cases) (15%)
3. Implementation of Iterator and Visitor patterns (10%)

Total: 100%

### Notes
1. Please implement your test cases reasonably; otherwise, you will get no points for that sub-problem.
2. TA will use the `_TA` project in Jenkins to test your program.
3. Calling `add_item` on a leaf node (`Book`, `ReferenceBook`, `EBook`) must throw `std::runtime_error`.
4. The same fine calculation rules from previous assignments still apply (`days_overdue <= 0` returns `0.0`).
5. All header files marked "(provided by TA)" contain only class declarations. The corresponding `.cpp` files (e.g., `null_iterator.cpp`, `book_bundle_iterator.cpp`) are yours to implement. For `ItemCountVisitor` and `FineCalculationVisitor`, both the `.h` (provided) and `.cpp` (implement yourself) are required.
6. Your program and tests should not have any memory leaks. Points may be deducted if memory leaks are found.
