#pragma once

#include <windows.h>

typedef struct _CBitMap {
    HDC      m_hdc;
    HDC      m_MemDC;
    HBITMAP  m_bitMap;
    HBITMAP  m_oldbitMap;
} CBitMap;

// 함수 선언
// 초기화 및 해제 함수
void CBitMap_Initialize(CBitMap* pThis);
void CBitMap_Release(CBitMap* pThis);

// 기능 함수들
HDC         CBitMap_GetMemDC(CBitMap* pThis);
CBitMap*    CBitMap_LoadBmp(CBitMap* pThis, PTCHAR pFileName);
CBitMap*    CBitMap_LoadBmp_Resource(CBitMap* pThis, int ResourceName);
