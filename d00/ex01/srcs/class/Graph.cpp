#include "class/Graph.hpp"

Graph::Graph(float width, float height) : size(width, height) {}

void Graph::addPoint(const Vector2& point) {
    points.push_back(point);
}

void Graph::addPoint(float x, float y) {
    points.push_back(Vector2(x, y));
}

void Graph::drawLine(const Vector2& start, const Vector2& end) {
    // Bresenham's line algorithm or any simple line drawing algorithm can be used here
    // This is a simple placeholder for illustration purposes
    float dx = end.getX() - start.getX();
    float dy = end.getY() - start.getY();
    float steps = std::max(std::abs(dx), std::abs(dy));
    float xInc = dx / steps;
    float yInc = dy / steps;

    float x = start.getX();
    float y = start.getY();

    for (int i = 0; i <= steps; ++i) {
        addPoint(x, y);
        x += xInc;
        y += yInc;
    }
}

void Graph::display() const {
    for (int y = static_cast<int>(size.getY()); y >= 0; --y) {
        for (int x = 0; x <= static_cast<int>(size.getX()); ++x) {
            bool pointFound = false;

            // for (const auto& point : points) {
			for (std::vector<Vector2>::const_iterator it = points.begin(); it != points.end(); ++it) {	
				const Vector2& point = *it;
                if (static_cast<int>(point.getX()) == x && static_cast<int>(point.getY()) == y) {
                    std::cout << "X ";
                    pointFound = true;
                    break;
                }
            }
            if (!pointFound) {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}
