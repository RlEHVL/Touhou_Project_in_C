#ifndef COBJ_H
#define COBJ_H

#include <stdbool.h>
#include "CBridge.h"

typedef struct CObj {
    float x, y;               // 위치
    bool active;              // 활성화 여부
    struct CBridge* bridge;   // 연결된 Bridge
} CObj;

// 함수 선언
CObj* CObjFactory_CreateCBullet(float x, float y, struct CBridge* bridge);
void CObj_SetPos(CObj* pObj, float x, float y);
void CObj_Initialize(CObj* pObj);
bool CObj_IsActive(CObj* pObj);
void CObj_SetActive(CObj* pObj, bool active);

#endif // COBJ_H
