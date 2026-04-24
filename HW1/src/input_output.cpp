#include "input_output.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include <fstream>
#include <sstream>

InputOutput::Arguments InputOutput::parseArguments(int argc, char* argv[]) {
    Arguments args;
    if (argc > 1) args.input_file = argv[1];
    if (argc > 2) args.output_file = argv[2];

    std::string criteria = (argc > 3) ? argv[3] : "";
    std::string order = (argc > 4) ? argv[4] : "";

    if ((criteria == "area" || criteria == "perimeter") &&
        (order == "inc" || order == "dec")) {
        args.sort_criteria = criteria;
        args.sort_order = order;
    } else {
        args.sort_criteria = "";
        args.sort_order = "";
    }

    return args;
}

Shape* InputOutput::parseShape(const std::string& line) {
    std::istringstream iss(line);
    std::string type;
    char paren;
    iss >> type >> paren;  // read type and skip '('

    if (type == "Circle") {
        double r;
        iss >> r;
        return new Circle(r);
    }
    if (type == "Rectangle") {
        double l, w;
        iss >> l >> w;
        return new Rectangle(l, w);
    }
    if (type == "Triangle") {
        double a, b, c;
        iss >> a >> b >> c;
        return new Triangle(a, b, c);
    }

    return nullptr;
}

std::vector<Shape*> InputOutput::readShapesFromFile(const std::string& filename) {
    std::vector<Shape*> shapes;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        try {
            Shape* s = parseShape(line);
            if (s != nullptr) {
                shapes.push_back(s);
            }
        } catch (const std::string&) {
            // invalid shape — skip and continue
        }
    }
    return shapes;
}

void InputOutput::writeShapesToFile(const std::string& filename,
                                    const std::vector<Shape*>& shapes) {
    std::ofstream file(filename);
    for (Shape* s : shapes) {
        file << s->toString() << "\n";
    }
}
