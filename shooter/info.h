// info.h

#ifndef INFO_H
#define INFO_H

typedef struct {
    float fx, fy;
    float fcx, fcy;
    float speed;
} INFO;

INFO Info_Create(float x, float y, float cx, float cy, float speed);

#endif // INFO_H
