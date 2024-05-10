#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Vector2.hpp"
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

class Graph {
private:
    Vector2 size;
    std::vector<Vector2> points;

public:
    Graph(float width, float height);

    void addPoint(const Vector2& point);

    void addPoint(float x, float y);

    void drawLine(const Vector2& start, const Vector2& end);

    void display() const;
};
#endif
