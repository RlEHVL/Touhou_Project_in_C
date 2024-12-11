#include "CMouse.h"
#include <windows.h>

extern HWND g_hWnd; // Value.h에서 선언된 전역 핸들 가정

POINT CMouse_GetPos(void)
{
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(g_hWnd, &pt);
    return pt;
}

void CMouse_Construct(CMouse* pThis)
{
    (void)pThis; // 원본 생성자와 동일하게 아무 동작 없음
}

void CMouse_Destruct(CMouse* pThis)
{
    (void)pThis; // 원본 소멸자와 동일하게 아무 동작 없음
}
