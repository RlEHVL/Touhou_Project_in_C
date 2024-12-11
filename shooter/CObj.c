#include "CObj.h"
#include <stdlib.h>

/*
    *
    * 제작:동필
    * 도움이:지피티
*/

CObj* CObjFactory_CreateCBullet(float x, float y, struct CBridge* bridge) {
    CObj* obj = (CObj*)malloc(sizeof(CObj));
    obj->x = x;
    obj->y = y;
    obj->bridge = bridge;
    obj->active = true;
    return obj;
}

void CObj_SetPos(CObj* pObj, float x, float y) {
    pObj->x = x;
    pObj->y = y;
}

void CObj_Initialize(CObj* pObj) {
    pObj->active = true;
}

bool CObj_IsActive(CObj* pObj) {
    return pObj->active;
}

void CObj_SetActive(CObj* pObj, bool active) {
    pObj->active = active;
}
