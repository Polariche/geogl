#pragma once
#include <cmath>
class Point {
    
public:
    float x;
    float y;

    Point operator + (const Point& o) const {
        return {x+o.x, y+o.y};
    }

    Point operator - (const Point& o) const {
        return {x-o.x, y-o.y};
    }

    bool operator == (const Point& o) const {
        return x == o.x && y == o.y;
    }

    double Distance(const Point& o) const {
        return sqrt((x-o.x) * (x-o.x) + (y-o.y) * (y-o.y));
    }
};