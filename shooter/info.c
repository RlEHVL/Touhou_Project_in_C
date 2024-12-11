// info.c

#include "info.h"

/*
    *
    * 제작:동필
    * 도움이:지피티
*/

INFO Info_Create(float x, float y, float cx, float cy, float speed) {
    INFO info;
    info.fx = x;
    info.fy = y;
    info.fcx = cx;
    info.fcy = cy;
    info.speed = speed;
    return info;
}
