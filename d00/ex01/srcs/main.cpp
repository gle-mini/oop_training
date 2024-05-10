#include "class/Vector2.hpp"
#include "class/Graph.hpp"

int main() {
    Graph graph(5, 5);
    graph.addPoint(0, 0);
    graph.addPoint(2, 2);
    graph.addPoint(4, 2);
    graph.addPoint(2, 4);

    graph.display();

	std::cout << "------------------------------------" << std::endl;

    graph.drawLine(Vector2(0, 0), Vector2(4, 4));
    graph.display();

    // graph.readFromFile("points.txt");
    // graph.display();

    return 0;
}
