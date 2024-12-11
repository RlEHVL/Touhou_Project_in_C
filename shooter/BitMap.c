#include "BitMap.h"
#include <windows.h>

/*
    *
    * 제작:동필
    * 도움이:지피티
*/

// 외부 전역 변수
extern HWND g_hWnd;
extern HINSTANCE hInst;

void CBitMap_Construct(CBitMap* pThis)
{
    pThis->m_hdc = NULL;
    pThis->m_MemDC = NULL;
    pThis->m_bitMap = NULL;
    pThis->m_oldbitMap = NULL;
}

void CBitMap_Destruct(CBitMap* pThis)
{
    // 원본 소멸자: Release() 호출
    CBitMap_Release(pThis);
}

HDC CBitMap_GetMemDC(CBitMap* pThis)
{
    return pThis->m_MemDC;
}

CBitMap* CBitMap_LoadBmpFile(CBitMap* pThis, PTCHAR pFileName)
{
    pThis->m_hdc = GetDC(g_hWnd);
    pThis->m_MemDC = CreateCompatibleDC(pThis->m_hdc);

    pThis->m_bitMap = (HBITMAP)LoadImage(NULL, pFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

    if (!pThis->m_bitMap)
    {
        MessageBox(g_hWnd, pFileName, L"File Load False", NULL);
    }

    pThis->m_oldbitMap = (HBITMAP)SelectObject(pThis->m_MemDC, pThis->m_bitMap);

    ReleaseDC(g_hWnd, pThis->m_hdc);
    return pThis;
}

CBitMap* CBitMap_LoadBmpResource(CBitMap* pThis, int ResourceName)
{
    pThis->m_hdc = GetDC(g_hWnd);
    pThis->m_MemDC = CreateCompatibleDC(pThis->m_hdc);

    pThis->m_bitMap = LoadBitmap(hInst, MAKEINTRESOURCE(ResourceName));

    if (!pThis->m_bitMap)
    {
        MessageBox(g_hWnd, L"pFileName", L"File Load False", NULL);
    }

    pThis->m_oldbitMap = (HBITMAP)SelectObject(pThis->m_MemDC, pThis->m_bitMap);

    ReleaseDC(g_hWnd, pThis->m_hdc);

    return pThis;
}

void CBitMap_Release(CBitMap* pThis)
{
    if (pThis->m_MemDC && pThis->m_oldbitMap) {
        SelectObject(pThis->m_MemDC, pThis->m_oldbitMap);
    }
    if (pThis->m_bitMap) {
        DeleteObject(pThis->m_bitMap);
        pThis->m_bitMap = NULL;
    }
    if (pThis->m_oldbitMap) {
        DeleteObject(pThis->m_oldbitMap);
        pThis->m_oldbitMap = NULL;
    }
    if (pThis->m_MemDC) {
        DeleteDC(pThis->m_MemDC);
        pThis->m_MemDC = NULL;
    }
}
