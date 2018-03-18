#ifndef PROGRAMMING_PEARLS_PAINTER_H
#define PROGRAMMING_PEARLS_PAINTER_H

#include "turtle.h"

class Painter {
    Turtle *turtle;
public:
    Painter(Turtle *turtle) : turtle(turtle) {}

    bool DrawCircle(int, int, int) {
        turtle->PenDown();
        turtle->Forward(100);
        turtle->Forward(50);
        return true;
    }
};

#endif //PROGRAMMING_PEARLS_PAINTER_H
