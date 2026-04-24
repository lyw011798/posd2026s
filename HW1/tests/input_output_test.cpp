#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <cstdio>
#include "input_output.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include <unistd.h>     
#include <filesystem>
#include <stdexcept>
#include <string>

// ---- parseArguments tests (existing) ----

TEST(InputOutputTest, ParseArgumentsValid) {
    const char* argv[] = {"./geo", "input.txt", "output.txt", "area", "inc"};
    int argc = 5;
    InputOutput::Arguments args = InputOutput::parseArguments(argc, (char**)argv);

    EXPECT_EQ(args.input_file, "input.txt");
    EXPECT_EQ(args.output_file, "output.txt");
    EXPECT_EQ(args.sort_criteria, "area");
    EXPECT_EQ(args.sort_order, "inc");
}

TEST(InputOutputTest, ParseArgumentsMissingOptional) {
    const char* argv[] = {"./geo", "input.txt", "output.txt"};
    int argc = 3;
    InputOutput::Arguments args = InputOutput::parseArguments(argc, (char**)argv);
    EXPECT_EQ(args.input_file, "input.txt");
    EXPECT_EQ(args.output_file, "output.txt");
    EXPECT_EQ(args.sort_criteria, "");
    EXPECT_EQ(args.sort_order, "");
}

TEST(InputOutputTest, ParseArgumentsInvalidCriteria) {
    const char* argv[] = {"./geo", "input.txt", "output.txt", "volume", "inc"};
    int argc = 5;
    InputOutput::Arguments args = InputOutput::parseArguments(argc, (char**)argv);
    EXPECT_EQ(args.sort_criteria, "");
    EXPECT_EQ(args.sort_order, "");
}

TEST(InputOutputTest, ParseArgumentsInvalidOrder) {
    const char* argv[] = {"./geo", "input.txt", "output.txt", "area", "random"};
    int argc = 5;
    InputOutput::Arguments args = InputOutput::parseArguments(argc, (char**)argv);
    EXPECT_EQ(args.sort_criteria, "");
    EXPECT_EQ(args.sort_order, "");
}

// ---- parseShape tests ----

TEST(InputOutputTest, ParseShapeCircle) {
    Shape* s = InputOutput::parseShape("Circle (5)");
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->toString(), "Circle (5)");
    delete s;
}

TEST(InputOutputTest, ParseShapeRectangle) {
    Shape* s = InputOutput::parseShape("Rectangle (3 4)");
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->toString(), "Rectangle (3 4)");
    delete s;
}

TEST(InputOutputTest, ParseShapeTriangle) {
    Shape* s = InputOutput::parseShape("Triangle (3 4 5)");
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->toString(), "Triangle (3 4 5)");
    delete s;
}

TEST(InputOutputTest, ParseShapeInvalidShapeType) {
    Shape* s = InputOutput::parseShape("InvalidLine");
    EXPECT_EQ(s, nullptr);
}

TEST(InputOutputTest, ParseShapeInvalidCircleRadius) {
    // Circle with radius 0 should throw
    EXPECT_THROW(InputOutput::parseShape("Circle (0)"), std::string);
}

TEST(InputOutputTest, ParseShapeInvalidTriangle) {
    EXPECT_THROW(InputOutput::parseShape("Triangle (1 1 3)"), std::string);
}

TEST(InputOutputTest, ParseShapeInvalidRectangle) {
    EXPECT_THROW(InputOutput::parseShape("Rectangle (0 4)"), std::string);
}

TEST(InputOutputTest, ParseShapeNonInteger) {
    Shape* s = InputOutput::parseShape("Circle (5.12)");
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s->toString(), "Circle (5.12)");
    delete s;
}

// ---- readShapesFromFile tests ----

static std::string makeTempFilePath() {
    std::string pattern = (std::filesystem::temp_directory_path() / "geo_test_XXXXXX").string();
    std::vector<char> buf(pattern.begin(), pattern.end());
    buf.push_back('\0');

    int fd = mkstemp(buf.data());
    if (fd == -1) {
        throw std::runtime_error("mkstemp failed");
    }
    close(fd);  
    return std::string(buf.data());
}

TEST(InputOutputTest, ReadShapesFromFile) {
    // Create a temp file with 6 valid + 8 invalid entries
    std::string tmpPath = makeTempFilePath();
    {
        std::ofstream f(tmpPath);
        f << "Circle (10)\n";
        f << "Rectangle (5.5 2.5)\n";
        f << "Triangle (5 12 13)\n";
        f << "Circle (3.5)\n";
        f << "Rectangle (7 3)\n";
        f << "Triangle (6 8 10)\n";
        // invalid entries
        f << "Circle (0)\n";
        f << "Triangle (1 1 3)\n";
        f << "Rectangle (0 4)\n";
        f << "Rectangle (-1 5)\n";
        f << "Circle (-3)\n";
        f << "Triangle (1 2 10)\n";
        f << "InvalidShape\n";
        f << "NotAShape (1 2)\n";
    }
    std::vector<Shape*> shapes = InputOutput::readShapesFromFile(tmpPath);
    ASSERT_EQ(shapes.size(), 6u);
    EXPECT_EQ(shapes[0]->toString(), "Circle (10)");
    EXPECT_EQ(shapes[1]->toString(), "Rectangle (5.5 2.5)");
    EXPECT_EQ(shapes[2]->toString(), "Triangle (5 12 13)");
    EXPECT_EQ(shapes[3]->toString(), "Circle (3.5)");
    EXPECT_EQ(shapes[4]->toString(), "Rectangle (7 3)");
    EXPECT_EQ(shapes[5]->toString(), "Triangle (6 8 10)");
    for (Shape* s : shapes) delete s;
    std::remove(tmpPath.c_str());
}

// ---- writeShapesToFile tests ----

TEST(InputOutputTest, WriteShapesToFile) {
    std::string tmpPath = makeTempFilePath();
    std::vector<Shape*> shapes = {
        new Circle(5.0),
        new Rectangle(3.0, 4.0),
        new Triangle(3.0, 4.0, 5.0)
    };
    InputOutput::writeShapesToFile(tmpPath, shapes);

    std::ifstream f(tmpPath);
    std::string line;
    std::getline(f, line); EXPECT_EQ(line, "Circle (5)");
    std::getline(f, line); EXPECT_EQ(line, "Rectangle (3 4)");
    std::getline(f, line); EXPECT_EQ(line, "Triangle (3 4 5)");

    for (Shape* s : shapes) delete s;
    std::remove(tmpPath.c_str());
}

TEST(InputOutputTest, WriteShapesToFileEmpty) {
    std::string tmpPath = makeTempFilePath();
    std::vector<Shape*> shapes;
    InputOutput::writeShapesToFile(tmpPath, shapes);

    std::ifstream f(tmpPath);
    std::string line;
    EXPECT_FALSE(std::getline(f, line));  // file should be empty
    std::remove(tmpPath.c_str());
}
