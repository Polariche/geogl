#pragma once

#include "Point.h"

class Edge {
    
public:
    Point* p1;
    Point* p2;
    bool directed;

public:
    double GetLength();
};