#include "BreakingDependencies/Shapes.h"

int main(int argc, char* argv[])
{
    std::vector<Shape> shapes;

    shapes.emplace_back(Circle(2.0));
    shapes.emplace_back(Square(2.0));
    shapes.emplace_back(Circle(4.0));
    shapes.emplace_back(Square(4.0), [](Square const& square)
                        { std::cout << "this is a new implemantation!" << std::endl; });

    drawAllShapes(shapes);
}
