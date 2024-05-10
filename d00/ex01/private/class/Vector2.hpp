#ifndef VECTOR2_HPP
#define VECTOR2_HPP

class Vector2 {
private:
    float x;
	float y;

public:
    Vector2(float x = 0, float y = 0);

    float getX() const;
    float getY() const;

    void setX(float newX);
    void setY(float newY);
};
#endif
