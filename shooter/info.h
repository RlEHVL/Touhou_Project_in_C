// info.h

#ifndef INFO_H
#define INFO_H

/*
    *
    * 제작:동필
    * 도움이:지피티
*/

typedef struct {
    float fx, fy;
    float fcx, fcy;
    float speed;
} INFO;

INFO Info_Create(float x, float y, float cx, float cy, float speed);

#endif // INFO_H
