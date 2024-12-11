#include "CBridge.h"

/*
    *
    * 제작:동필
    * 도움이:지피티
*/

void CBridge_SetAngle(CBridge* pBridge, float angle) {
    pBridge->angle = angle;
}

void CBullet_Bridge_SetType(CBridge* pBridge, int typeNum) {
    pBridge->type = typeNum;
}

void CBullet_Bridge_SetSpeed(CBridge* pBridge, float speed) {
    pBridge->speed = speed;
}
