#include "input_output.h"
#include "sort.h"
#include "sortstrategy.h"
#include "sorter.h"

int main(int argc, char* argv[]) {
    // T5.1: Parse CLI arguments
    InputOutput::Arguments args = InputOutput::parseArguments(argc, argv);

    // T5.2: Read shapes from input file
    std::vector<Shape*> shapes = InputOutput::readShapesFromFile(args.input_file);

    // T5.3: Sort shapes if valid criteria were provided
    if (!args.sort_criteria.empty() && !args.sort_order.empty()) {
        std::unique_ptr<SortStrategy> strategy;

        if (args.sort_criteria == "area" && args.sort_order == "inc") {
            strategy = std::make_unique<AreaIncreasingStrategy>();
        } else if (args.sort_criteria == "area" && args.sort_order == "dec") {
            strategy = std::make_unique<AreaDecreasingStrategy>();
        } else if (args.sort_criteria == "perimeter" && args.sort_order == "inc") {
            strategy = std::make_unique<PerimeterIncreasingStrategy>();
        } else if (args.sort_criteria == "perimeter" && args.sort_order == "dec") {
            strategy = std::make_unique<PerimeterDecreasingStrategy>();
        }

        if (strategy) {
            Sorter sorter(std::move(strategy));
            sorter.sort(shapes);
        }
    }

    // T5.4: Write shapes to output file
    InputOutput::writeShapesToFile(args.output_file, shapes);

    // T5.5: Free heap-allocated shapes
    for (Shape* s : shapes) {
        delete s;
    }

    return 0;
}
