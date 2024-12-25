#include <cmath>
#include "Edge.h"

double Edge::GetLength() {
    Point p = *p2 - *p1;
    return sqrt(p.x * p.x + p.y * p.y);
}