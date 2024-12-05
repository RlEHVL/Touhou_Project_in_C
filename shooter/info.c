// info.c

#include "info.h"

INFO Info_Create(float x, float y, float cx, float cy, float speed) {
    INFO info;
    info.fx = x;
    info.fy = y;
    info.fcx = cx;
    info.fcy = cy;
    info.speed = speed;
    return info;
}
