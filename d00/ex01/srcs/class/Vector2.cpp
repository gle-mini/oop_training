#include "class/Vector2.hpp"

Vector2::Vector2(float x, float y) : x(x), y(y) {}

float Vector2::getX() const { return x; }
float Vector2::getY() const { return y; }

void Vector2::setX(float newX) { this->x = newX; }
void Vector2::setY(float newY) { this->y = newY; }
