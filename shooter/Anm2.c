#include "CAnm2.h"
#include <math.h>
#include <stdlib.h>

extern float CMathMgr_GetAngle(void* pTarget, void* pObj);
extern INFO GetInfo(void* pObj);
extern void SetInfo(void* pObj, INFO info);
extern void* GetBitMap(void* pObj);
extern DWORD GetTickCount();
extern int WINCX;
extern int WINCY;
extern float PI;
extern int 삭제; // »èÁ¦
extern HDC CBitMap_GetMemDC(void* pBitmap);
extern void* Map_GetBitmap(void* pMap, const wchar_t* key);

// Bullet 함수들 (C 스타일)
extern void CreateBullet_CNormalBulletA(float fx, float fy, float angle, int abl, ...);
extern void CreateBullet_CBounceBullet(float fx, float fy, float angle, int abl);

// Pattern
void CAnm2_Pattern(CAnm2* pThis)
{
    INFO tinfo = GetInfo(pThis->m_pObj);
    switch (pThis->m_iPhase)
    {
    case 0:
        pThis->m_fSpeed = 1.f;
        break;
    case 1:
        pThis->m_fSpeed = 0.f;
        if (pThis->m_dwTime + 5000 < GetTickCount())
        {
            pThis->m_iPhase = 2;
        }
        break;
    case 2:
        pThis->m_fSpeed = 1.f;
        if (tinfo.fx > WINCX / 2)
        {
            pThis->m_fAngle = 60.f;
        }
        else
        {
            pThis->m_fAngle = 120.f;
        }
        pThis->m_dwCoolTime = GetTickCount() + 10000;
        break;
    default:
        break;
    }
}

// Initialize
void CAnm2_Initialize(CAnm2* pThis)
{
    pThis->m_pMapBmp = GetBitMap(pThis->m_pObj);
    pThis->m_tStat = (STAT){600,600}; // STAT(600)
    INFO tinfo = GetInfo(pThis->m_pObj);
    tinfo.fcx = 140;
    tinfo.fcy = 128;

    SetInfo(pThis->m_pObj, tinfo);
    pThis->m_dwTime = GetTickCount();
    pThis->m_dwCoolTime = GetTickCount() + 3000;

    pThis->m_fSpeed = 1.f;
    pThis->m_fAngle = 270.f;
}

// Progress
int CAnm2_Progress(CAnm2* pThis, INFO* rInfo)
{
    CAnm2_Pattern(pThis);

    rInfo->fx += cosf(pThis->m_fAngle * PI / 180.0f) * pThis->m_fSpeed;
    rInfo->fy -= sinf(pThis->m_fAngle * PI / 180.0f) * pThis->m_fSpeed;

    if (rInfo->fx < -200 || rInfo->fx > WINCX + 200 || rInfo->fy < -200 || rInfo->fy > WINCY + 200)
        return 삭제;

    if (pThis->m_tStat.iHP <= 0)
        return 삭제;

    if (pThis->m_dwCoolTime < GetTickCount())
    {
        pThis->m_dwCoolTime += rand() % 3 * 250 + 2500;
        float TargetAngle = CMathMgr_GetAngle(pThis->m_pTarget, pThis->m_pObj) + rand() % 7 - 3;
        for (int i = -30; i <= 30; i += 10)
        {
            CAnm2_ShootSpeed(pThis, TargetAngle + i, 2.0f);
            CAnm2_ShootSpeed(pThis, TargetAngle + i, 2.3f);
            CAnm2_ShootSpeed(pThis, TargetAngle + i, 2.6f);
            CAnm2_ShootSpeed(pThis, TargetAngle + i, 2.9f);
            CAnm2_ShootSpeed(pThis, TargetAngle + i, 3.2f);
        }
        CAnm2_ShootXYAngle(pThis, -50, 0, 225);
        CAnm2_ShootXYAngle(pThis, 50, 0, 315);
    }

    if (rInfo->fy > WINCY / 3 && pThis->m_iPhase == 0)
    {
        pThis->m_iPhase = 1;
        pThis->m_dwTime = GetTickCount();
    }

    return 0;
}

// Render
void CAnm2_Render(CAnm2* pThis, HDC hdc)
{
    INFO tinfo = GetInfo(pThis->m_pObj);
    void* pMonsterBmp = Map_GetBitmap(pThis->m_pMapBmp, L"Monster2");
    HDC hMemDC = CBitMap_GetMemDC(pMonsterBmp);

    TransparentBlt(hdc,
        (int)(tinfo.fx - tinfo.fcx / 2),
        (int)(tinfo.fy - tinfo.fcy / 2),
        (int)tinfo.fcx, (int)tinfo.fcy,
        hMemDC,
        0, 0,
        (int)tinfo.fcx, (int)tinfo.fcy,
        RGB(255, 255, 255));
}

// Release
void CAnm2_Release(CAnm2* pThis)
{
    (void)pThis; 
}

// Shoot 계열 함수
void CAnm2_Shoot(CAnm2* pThis, float _angle)
{
    INFO tinfo = GetInfo(pThis->m_pObj);
    CreateBullet_CNormalBulletA(tinfo.fx, tinfo.fy, _angle, ABL_NORMAL);
}

void CAnm2_ShootSpeed(CAnm2* pThis, float _angle, float _speed)
{
    INFO tinfo = GetInfo(pThis->m_pObj);
    // 원본: CreateBullet<CNormalBulletA>(tinfo.fx, tinfo.fy, _angle, ABL_NORMAL, 0, _speed, 2);
    CreateBullet_CNormalBulletA(tinfo.fx, tinfo.fy, _angle, ABL_NORMAL, 0, _speed, 2);
}

void CAnm2_ShootXY(CAnm2* pThis, float _x, float _y)
{
    INFO tinfo = GetInfo(pThis->m_pObj);
    tinfo.fx += _x;
    tinfo.fy += _y;
    float TargetAngle = CMathMgr_GetAngle(pThis->m_pTarget, tinfo) + rand() % 7 - 3;
    CreateBullet_CNormalBulletA(tinfo.fx, tinfo.fy, TargetAngle, ABL_NORMAL, 0, 3.5f);
}

void CAnm2_ShootXYAngle(CAnm2* pThis, float _x, float _y, float _angle)
{
    INFO tinfo = GetInfo(pThis->m_pObj);
    tinfo.fx += _x;
    tinfo.fy += _y;
    CreateBullet_CBounceBullet(tinfo.fx, tinfo.fy, _angle, ABL_BOUNCE);
}
