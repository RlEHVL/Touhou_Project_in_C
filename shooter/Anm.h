#pragma once
#include <windows.h>
#include "Monster_Bridge.h" // C 스타일로 변환된 Monster_Bridge를 사용한다고 가정

#ifdef __cplusplus
extern "C" {
#endif

// CMonster_Bridge가 가진 멤버를 여기 포함해야 한다.
// 원래 CMonster_Bridge가 C++ 클래스였으나 C로 변환 시 필요한 필드와
// 함수 포인터 등을 직접 포함하거나, 공용 구조체로 관리.
// 여기서는 간단히 CMonster_Bridge가 필요한 멤버를 CAnm1에 직접 포함한다고 가정.

typedef struct _CAnm1 {
    void* m_pObj;
    void* m_pTarget;
    STAT  m_tStat;     // 몬스터 HP 등 상태
    int   m_iPhase;
    float m_fAngle;
    void* m_pMapBmp;
    DWORD m_dwTime;
    DWORD m_dwCoolTime;
    INFO  m_BmpInfo;
    float m_fSpeed;
} CAnm1;

// 원본 private 멤버함수 Pattern, Shoot도 전역 함수로 변환
void CAnm1_Pattern(CAnm1* pThis);
void CAnm1_Shoot(CAnm1* pThis, float _angle);

// 원본 public 멤버 함수
void CAnm1_Initialize(CAnm1* pThis);
int  CAnm1_Progress(CAnm1* pThis, INFO* rInfo);
void CAnm1_Render(CAnm1* pThis, HDC hdc);
void CAnm1_Release(CAnm1* pThis);

// Clone 기능도 C로 구현하려면, CAnm1을 복사하는 함수를 만든다.
CAnm1* CAnm1_Clone(CAnm1* pSrc);

// 생성자/소멸자 대응
void CAnm1_Construct(CAnm1* pThis);
void CAnm1_Destruct(CAnm1* pThis);

#ifdef __cplusplus
}
#endif
