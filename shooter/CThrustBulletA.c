#include "CThrustBulletA.h"

void CThrustBulletA_SetTarget(CBridge* pBridge, struct CObj* pTarget) {
    pBridge->target = pTarget;
}

void CThrustBulletA_SetTime(CBridge* pBridge, int time) {
    pBridge->time = time;
}
