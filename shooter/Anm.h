#pragma once
#include <windows.h>
#include "Monster_Bridge.h"

// CAnm1 구조체 정의
typedef struct _CAnm1 {
    // 원래 CMonster_Bridge 상속받았으므로 필요한 멤버를 직접 포함
    void* m_pObj;
    void* m_pTarget;
    STAT m_tStat;
    int m_iPhase;
    float m_fAngle;
    void* m_pMapBmp;
    DWORD m_dwTime;
    DWORD m_dwCoolTime;
    INFO m_BmpInfo;
    float m_fSpeed;
} CAnm1;

#ifdef __cplusplus
extern "C" {
#endif

void CAnm1_Initialize(CAnm1* pThis);
int  CAnm1_Progress(CAnm1* pThis, INFO* rInfo);
void CAnm1_Render(CAnm1* pThis, HDC hdc);
void CAnm1_Release(CAnm1* pThis);
void CAnm1_Pattern(CAnm1* pThis);
void CAnm1_Shoot(CAnm1* pThis, float _angle);

// 원래는 C++ 생성자/소멸자였지만 C에서는 직접 init 함수나 malloc 등으로 관리
void CAnm1_Construct(CAnm1* pThis);
void CAnm1_Destruct(CAnm1* pThis);

#ifdef __cplusplus
}
#endif
