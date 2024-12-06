#ifndef CBRIDGE_H
#define CBRIDGE_H

typedef struct CBridge {
    float angle;
    int type;
    float speed;
    struct CObj* target;
    int time;
} CBridge;

// 함수 선언
void CBridge_SetAngle(CBridge* pBridge, float angle);
void CBullet_Bridge_SetType(CBridge* pBridge, int typeNum);
void CBullet_Bridge_SetSpeed(CBridge* pBridge, float speed);

#endif // CBRIDGE_H
