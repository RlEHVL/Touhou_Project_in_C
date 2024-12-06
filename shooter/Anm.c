#pragma once
#include <windows.h>
// 외부 정의된 함수, 상수, 매크로들 가정
// 예:
// extern float CMathMgr_GetAngle(void* pTarget, void* pObj);
// extern void CreateBullet_CNormalBulletA(float fx, float fy, float angle, int abl, int time, float fSpeed, ...);
// extern INFO GetInfo(void* pObj);
// extern void SetInfo(void* pObj, INFO info);
// extern void* GetBitMap(void* pObj);
// extern DWORD GetTickCount();
// extern int WINCX;
// extern int WINCY;
// extern float PI;
// extern int 삭제; // »èÁ¦
// extern void* Map_GetBitmap(void* pMap, const wchar_t* key);
// extern HDC CBitMap_GetMemDC(void* pBitmap);
// extern int ABL_NORMAL;
// #define STAT(x) ((STAT){(x),(x)})
// #define INFO(x,y,w,h) ((INFO){(x),(y),(w),(h),0})

typedef struct _STAT {
    int iHP;
    int iMaxHP;
} STAT;

typedef struct _INFO {
    float fx;
    float fy;
    float fcx;
    float fcy;
    int iLayer;
} INFO;

typedef struct _CAnm1 {
    void* m_pObj;
    void* m_pTarget;
    STAT  m_tStat;
    int   m_iPhase;
    float m_fAngle;
    void* m_pMapBmp;
    DWORD m_dwTime;
    DWORD m_dwCoolTime;
    INFO  m_BmpInfo;
    float m_fSpeed;
} CAnm1;

// Pattern 함수 (CAnm1::Pattern)
void CAnm1_Pattern(CAnm1* pThis)
{
    switch (pThis->m_iPhase)
    {
    case 0:
        pThis->m_fAngle -= 0.3f;
        break;
    case 1:
        pThis->m_fAngle += 0.3f;
        break;
    case 2:
        pThis->m_fAngle -= 0.4f;
        break;
    case 3:
        pThis->m_fAngle += 0.4f;
        break;
    default:
        break;
    }
}

// Shoot 함수 (CAnm1::Shoot)
void CAnm1_Shoot(CAnm1* pThis, float _angle)
{
    INFO tinfo = GetInfo(pThis->m_pObj);
    CreateBullet_CNormalBulletA(tinfo.fx, tinfo.fy, _angle + rand()%7 - 3, ABL_NORMAL, 0, 3.5f);
}

// Initialize (CAnm1::Initialize)
void CAnm1_Initialize(CAnm1* pThis)
{
    switch (pThis->m_iPhase)
    {
    case 0:
        pThis->m_fAngle = 230.f;
        break;
    case 1:
        pThis->m_fAngle = 310.f;
        break;
    case 2:
        pThis->m_fAngle = 260.f;
        break;
    case 3:
        pThis->m_fAngle = 280.f;
        break;
    default:
        break;
    }
    pThis->m_pMapBmp = GetBitMap(pThis->m_pObj);
    pThis->m_tStat = (STAT){20,20};
    INFO tinfo = GetInfo(pThis->m_pObj);
    tinfo.fcx = 50;
    tinfo.fcy = 50;

    SetInfo(pThis->m_pObj, tinfo);
    pThis->m_dwTime = GetTickCount();
    pThis->m_dwCoolTime = rand() % 3 * 250 + 1250;

    pThis->m_BmpInfo = (INFO){6,11,50,50,0};

    pThis->m_fSpeed = 3.f;
}

// Progress (CAnm1::Progress)
int CAnm1_Progress(CAnm1* pThis, INFO* rInfo)
{
    CAnm1_Pattern(pThis);

    rInfo->fx += cosf(pThis->m_fAngle * PI / 180.0f) * pThis->m_fSpeed;
    rInfo->fy -= sinf(pThis->m_fAngle * PI / 180.0f) * pThis->m_fSpeed;

    if (rInfo->fx < -200 || rInfo->fx > WINCX + 200 || rInfo->fy < -200 || rInfo->fy > WINCY + 200)
        return 삭제;

    if (pThis->m_tStat.iHP <= 0)
        return 삭제;

    if (pThis->m_dwTime + pThis->m_dwCoolTime < GetTickCount())
    {
        pThis->m_dwTime = GetTickCount();
        pThis->m_dwCoolTime = rand() % 3 * 250 + 1250;
        float TargetAngle = CMathMgr_GetAngle(pThis->m_pTarget, pThis->m_pObj);
        CAnm1_Shoot(pThis, TargetAngle);
    }

    return 0;
}

// Render (CAnm1::Render)
void CAnm1_Render(CAnm1* pThis, HDC hdc)
{
    INFO tinfo = GetInfo(pThis->m_pObj);
    void* pMonsterBmp = Map_GetBitmap(pThis->m_pMapBmp, L"Monster");
    HDC hMemDC = CBitMap_GetMemDC(pMonsterBmp);

    TransparentBlt(hdc,
        (int)(tinfo.fx - tinfo.fcx / 2),
        (int)(tinfo.fy - tinfo.fcy / 2),
        (int)tinfo.fcx, (int)tinfo.fcy,
        hMemDC,
        (int)(pThis->m_BmpInfo.fx),
        (int)(pThis->m_BmpInfo.fy),
        (int)tinfo.fcx, (int)tinfo.fcy,
        RGB(255, 255, 255));
}

// Release (CAnm1::Release)
void CAnm1_Release(CAnm1* pThis)
{
    (void)pThis; // 사용하지 않는 매개변수 경고 방지
}
