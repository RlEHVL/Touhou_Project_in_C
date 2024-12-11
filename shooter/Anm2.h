#ifndef CANM2_H
#define CANM2_H

#include "Monster_Bridge.h"

/*
    *
    * 제작:동필
    * 도움이:지피티
*/

// CAnm2 구조체 정의
typedef struct CAnm2 {
    CMonster_Bridge base; // CMonster_Bridge를 포함하여 상속과 유사한 구조 생성

    // CAnm2의 멤버 변수
    DWORD m_dwTime;
    DWORD m_dwCoolTime;
    float m_fSpeed;
    float m_fAngle;
    int m_iPhase;
} CAnm2;

// 함수 선언 (멤버 함수에 해당)
void CAnm2_Construct(CAnm2* self);
void CAnm2_Destruct(CAnm2* self);
void CAnm2_Pattern(CAnm2* self);
void CAnm2_Initialize(CAnm2* self);
int CAnm2_Progress(CAnm2* self, INFO* rInfo);
void CAnm2_Render(CAnm2* self, HDC hdc);
void CAnm2_Release(CAnm2* self);

// Shoot 관련 함수들
void CAnm2_Shoot(CAnm2* self, float angle);
void CAnm2_ShootSpeed(CAnm2* self, float angle, float speed);
void CAnm2_ShootPosition(CAnm2* self, float x, float y);
void CAnm2_ShootPositionAngle(CAnm2* self, float x, float y, float angle);

#endif // CANM2_H
