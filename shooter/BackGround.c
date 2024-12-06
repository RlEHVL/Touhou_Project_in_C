#include "BackGround.h"
#include <windows.h>

extern int WINCX;
extern int WINCY;
extern HDC CBitMap_GetMemDC(void* pBitmap);
extern void* Map_GetBitmap(void* pMap, const wchar_t* key);

void CBackGround_Construct(CBackGround* pThis)
{
    // 필요 시 초기화
    pThis->m_pMapBmp = NULL;
    pThis->m_tInfo = (INFO){0,0,WINCX,WINCY,0};
}

void CBackGround_Destruct(CBackGround* pThis)
{
    (void)pThis;
}

void CBackGround_Initialize(CBackGround* pThis)
{
    // 원본 Initialize 빈 함수
    (void)pThis;
}

int CBackGround_Progress(CBackGround* pThis)
{
    (void)pThis;
    return 0;
}

void CBackGround_Render(CBackGround* pThis, HDC hdc)
{
    void* pBackBmp = Map_GetBitmap(pThis->m_pMapBmp, L"BackGround");
    HDC hMemDC = CBitMap_GetMemDC(pBackBmp);

    // BitBlt와 동일 로직
    extern int WINCX;
    extern int WINCY;
    BitBlt(hdc,
        0, 0, WINCX, WINCY,
        hMemDC,
        0, 0,
        SRCCOPY);
}

void CBackGround_Release(CBackGround* pThis)
{
    (void)pThis; //컴파일 에러 방지
}
