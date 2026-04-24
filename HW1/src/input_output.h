#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include "shape.h"
#include <string>
#include <vector>

class InputOutput {
public:
    struct Arguments {
        std::string input_file;
        std::string output_file;
        std::string sort_criteria;
        std::string sort_order;
    };

    static Arguments parseArguments(int argc, char* argv[]);
    static Shape* parseShape(const std::string& line);
    static std::vector<Shape*> readShapesFromFile(const std::string& filename);
    static void writeShapesToFile(const std::string& filename,
                                  const std::vector<Shape*>& shapes);
};

#endif
