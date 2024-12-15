#pragma once

#include <math.h>

typedef struct {
    double x, y;
} Vec2d;

Vec2d addVec2d(Vec2d a, Vec2d b) {
    Vec2d result = { a.x + b.x, a.y + b.y };
    return result;
}

Vec2d subVec2d(Vec2d a, Vec2d b) {
    Vec2d result = { a.x - b.x, a.y - b.y };
    return result;
}

double distance(Vec2d a, Vec2d b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
