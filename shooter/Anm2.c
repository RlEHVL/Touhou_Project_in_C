#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "info.h"   
#include "bitmap.h" 
#include "mathmgr.h" 
#include "bullet.h" 

#define WINCX 800
#define WINCY 600
#define PI 3.14159265358979323846

typedef struct {
    float fx, fy;  // 위치
    float fcx, fcy; // 크기
} INFO;

typedef struct {
    INFO info;
    int iHP;
} STAT;

typedef struct {
    INFO* m_pObj;
    INFO* m_pTarget;
    BITMAP* m_pMapBmp;
    STAT m_tStat;
    float m_fSpeed;
    float m_fAngle;
    int m_iPhase;
    unsigned int m_dwTime;
    unsigned int m_dwCoolTime;
} CAnm2;

void CAnm2_Initialize(CAnm2* self);
int CAnm2_Progress(CAnm2* self, INFO* rInfo);
void CAnm2_Render(CAnm2* self, void* hdc);
void CAnm2_Release(CAnm2* self);
void CAnm2_Shoot(CAnm2* self, float _angle);
void CAnm2_ShootSpeed(CAnm2* self, float _angle, float _speed);
void CAnm2_ShootXY(CAnm2* self, float _x, float _y);
void CAnm2_ShootXYAngle(CAnm2* self, float _x, float _y, float _angle);

// 패턴 처리 함수
void CAnm2_Pattern(CAnm2* self) {
    INFO tinfo = *(self->m_pObj);
    switch (self->m_iPhase) {
        case 0:
            self->m_fSpeed = 1.f;
            break;
        case 1:
            self->m_fSpeed = 0.f;
            if (self->m_dwTime + 5000 < clock()) {
                self->m_iPhase = 2;
            }
            break;
        case 2:
            self->m_fSpeed = 1.f;
            if (tinfo.fx > WINCX / 2) {
                self->m_fAngle = 60.f;
            } else {
                self->m_fAngle = 120.f;
            }
            self->m_dwCoolTime = clock() + 10000;
            break;
        default:
            break;
    }
}

// 초기화 함수
void CAnm2_Initialize(CAnm2* self) {
    self->m_pMapBmp = self->m_pObj;
    self->m_tStat.iHP = 600;
    self->m_pObj->fcx = 140;
    self->m_pObj->fcy = 128;
    self->m_dwTime = clock();
    self->m_dwCoolTime = clock() + 3000;
    self->m_fSpeed = 1.f;
    self->m_fAngle = 270.f;
}

// 진행 처리 함수
int CAnm2_Progress(CAnm2* self, INFO* rInfo) {
    CAnm2_Pattern(self);

    rInfo->fx += cosf(self->m_fAngle * PI / 180) * self->m_fSpeed;
    rInfo->fy -= sinf(self->m_fAngle * PI / 180) * self->m_fSpeed;

    if (rInfo->fx < -200 || rInfo->fx > WINCX + 200 || rInfo->fy < -200 || rInfo->fy > WINCY + 200)
        return -1;

    if (self->m_tStat.iHP <= 0)
        return -1;

    if (self->m_dwCoolTime < clock()) {
        self->m_dwCoolTime += rand() % 3 * 250 + 2500;
        float TargetAngle = CMathMgr_GetAngle(self->m_pTarget, self->m_pObj) + rand() % 7 - 3;
        for (int i = -30; i <= 30; i += 10) {
            CAnm2_ShootSpeed(self, TargetAngle + i, 2.0f);
            CAnm2_ShootSpeed(self, TargetAngle + i, 2.3f);
            CAnm2_ShootSpeed(self, TargetAngle + i, 2.6f);
        }
        CAnm2_ShootXYAngle(self, -50, 0, 225);
        CAnm2_ShootXYAngle(self, 50, 0, 315);
    }
    if (rInfo->fy > WINCY / 3 && self->m_iPhase == 0) {
        self->m_iPhase = 1;
        self->m_dwTime = clock();
    }

    return 0;
}

// 렌더링 함수
void CAnm2_Render(CAnm2* self, void* hdc) {
    INFO tinfo = *(self->m_pObj);
    TransparentBlt(hdc,
                   (int)(tinfo.fx - tinfo.fcx / 2),
                   (int)(tinfo.fy - tinfo.fcy / 2),
                   (int)tinfo.fcx, (int)tinfo.fcy,
                   self->m_pMapBmp->GetMemDC(),
                   0, 0,
                   (int)tinfo.fcx, (int)tinfo.fcy,
                   RGB(255, 255, 255));
}

// 메모리 해제 함수
void CAnm2_Release(CAnm2* self) {
    // 리소스 정리 필요 시 구현
}

// 총알 관련 함수
void CAnm2_Shoot(CAnm2* self, float _angle) {
    INFO tinfo = *(self->m_pObj);
    CreateBullet_Normal(tinfo.fx, tinfo.fy, _angle, 1);  // 총알 생성 함수
}

void CAnm2_ShootSpeed(CAnm2* self, float _angle, float _speed) {
    INFO tinfo = *(self->m_pObj);
    CreateBullet_Normal(tinfo.fx, tinfo.fy, _angle, 1, _speed);
}

void CAnm2_ShootXY(CAnm2* self, float _x, float _y) {
    INFO tinfo = *(self->m_pObj);
    tinfo.fx += _x;
    tinfo.fy += _y;
    float TargetAngle = CMathMgr_GetAngle(self->m_pTarget, tinfo) + rand() % 7 - 3;
    CreateBullet_Normal(tinfo.fx, tinfo.fy, TargetAngle, 1, 3.5f);
}

void CAnm2_ShootXYAngle(CAnm2* self, float _x, float _y, float _angle) {
    INFO tinfo = *(self->m_pObj);
    tinfo.fx += _x;
    tinfo.fy += _y;
    CreateBullet_Bounce(tinfo.fx, tinfo.fy, _angle, 2);  // 다른 총알 타입
}
