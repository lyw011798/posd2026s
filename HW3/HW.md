# Pattern-Oriented Software Design 2026 Spring Assignment

## Assignment 3

### Purpose of this assignment:
Let students practice the **Composite design pattern** in C++20.

### Background:
In this assignment, you will extend the `LibraryManagementSystem` by introducing a `BookBundle` class. A `BookBundle` will act as a collection of `LibraryItem` objects, allowing users to borrow an entire set of items (e.g., a "Sci-Fi Collection" or a "Lord of the Rings Trilogy") as a single unit. This requires implementing the **Composite pattern**, treating individual items (`Book`, `ReferenceBook`, `EBook`) and composite items (`BookBundle`) uniformly.

### Problems:
Please implement and test the following class and methods:

#### Composite Pattern Design — `add_item` in `LibraryItem`:
In the Composite pattern, the `add_item(LibraryItem* item)` method is declared as a **virtual method in the base class `LibraryItem`**. The default implementation in `LibraryItem` throws `std::runtime_error`, because leaf nodes (`Book`, `ReferenceBook`, `EBook`) cannot contain children. The composite class `BookBundle` **overrides** `add_item` to actually store child items. This design allows clients to call `add_item` through a `LibraryItem*` pointer without knowing the concrete type — if it is a bundle, the item is added; if it is a leaf, an exception is thrown.

#### Composite Class `BookBundle`:
- Inherits from `LibraryItem`
- **Constructor**: `BookBundle(long id, std::string title)`
  - The author of a `BookBundle` should logically be `"Multiple Authors"`.
- **Methods**:
  - `get_type()` - Returns `"BookBundle"`
  - `to_string()` - Returns a string representation of the bundle and all its contents. Each nesting level adds **2 spaces** of indentation. Format:
    ```
    Bundle: {title} (items: {number_of_items})
      {item1->to_string()}
      {item2->to_string()}
      ...
    ```
    For nested bundles, indentation accumulates. For example, a 3-level nesting:
    ```
    Bundle: Level1 (items: 1)
      Bundle: Level2 (items: 1)
        Bundle: Level3 (items: 1)
          Book: Deep Book by Author
    ```
  - `add_item(LibraryItem* item)` - Adds a `LibraryItem` to the bundle.
  - `get_items()` - Returns `const std::vector<LibraryItem*>&`, a read-only reference to the bundle's children. This is used by `FineStrategy` to recursively calculate fines.

### Fine Calculation for `BookBundle`:
- When `calculate_fine` is called on a `BookBundle`, the fine is the **sum of the fines** for all items in the bundle (calculated recursively for nested bundles).
- An **empty bundle** should return a fine of `0.0`.
- The same rules from Assignment 2 still apply: `calculate_fine` must return `0.0` when `days_overdue <= 0`, and `ProgressiveFineStrategy` uses the same 7-day threshold.
- For example, if a bundle contains a `Book` and an `EBook`, and the strategy is `StandardFineStrategy` with 3 days overdue, the fine is `(1.0 * 3) + (0.5 * 3) = 4.5`.

### Note:
- A `BookBundle` can contain other `BookBundle` objects (nested bundles). A nested bundle that is empty contributes `0.0` to the total fine.
- When a client calls `to_string()` on a `BookBundle`, it should recursively call `to_string()` on its children to format the output.
- You do *not* need to rewrite or remove the previous `FineStrategy` functionality; just ensure that `BookBundle` integrates safely as a `LibraryItem`.

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
    └── ut_library.cpp
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
    1. Implementation and tests of `BookBundle` basic operations (`add_item`, `get_type`, `to_string`) (15%)
    2. Implementation and tests of fine calculation for `BookBundle` (15%)
    3. Implementation and tests of nested `BookBundle` (10%)
2. Tests by TA (50%)
    1. Tests of `BookBundle` as a `LibraryItem` (polymorphism, `add_item` throws on leaf nodes) (10%)
    2. Tests of `BookBundle` `to_string` (flat and nested) (10%)
    3. Tests of fine calculation on `BookBundle` with all strategies (10%)
    4. Tests of fine calculation on nested `BookBundle` (10%)
    5. Tests of edge cases (empty bundle, zero/negative days overdue, progressive 7-day boundary) (10%)
3. Implementation of composite pattern (10%)

Total: 100%

### Notes
1. Please implement your test cases reasonably; otherwise, you will get no points for that sub-problem.
2. TA will use the `_TA` project in Jenkins to test your program.
3. Calling `add_item` on a leaf node (`Book`, `ReferenceBook`, `EBook`) must throw `std::runtime_error`.
4. The same fine calculation rules from Assignment 2 still apply (`days_overdue <= 0` returns `0.0`, `ProgressiveFineStrategy` 7-day threshold, etc.).
5. Your program and tests should not have any memory leaks. Points may be deducted if memory leaks are found.
