#include "BackGround.h"
#include <windows.h>

// 외부 변수 함수 가정
extern int WINCX;
extern int WINCY;
extern HDC CBitMap_GetMemDC(void* pBitmap);
extern void* Map_GetBitmap(void* pMap, const wchar_t* key);

// 원래 C++ 생성자
void CBackGround_Construct(CBackGround* pThis)
{
    // C++ 생성자 내용 없음
    // 필요 시 초기화
    pThis->m_pMapBmp = NULL;
    pThis->m_tInfo = (INFO){0,0,WINCX,WINCY,0};
}

// 원래 C++ 소멸자
void CBackGround_Destruct(CBackGround* pThis)
{
    // C++ 소멸자 내용 없음
    (void)pThis;
}

void CBackGround_Initialize(CBackGround* pThis)
{
    // 원본 Initialize 빈 함수
    (void)pThis;
}

int CBackGround_Progress(CBackGround* pThis)
{
    // 원본 return 0;
    (void)pThis;
    return 0;
}

void CBackGround_Render(CBackGround* pThis, HDC hdc)
{
    // 원본: (*m_pMapBmp)["BackGround"]->GetMemDC()
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
    // 원본 비어있음
    (void)pThis;
}
