#pragma once
#include "Value.h"

#ifdef __cplusplus
extern "C" {
#endif

// C에는 class가 없으므로 struct 사용.
// public 키워드는 의미가 없으나 형태상 남겨둘 수 있음.
// 단, 함수 정의를 struct 안에 넣을 수 없어 struct 뒤에 inline 함수 정의.
#define class struct
#define public /* public */

// 원본 class CMouse 정의를 최대한 비슷하게 유지
class CMouse
{
public:
    // 원본은 여기서 static POINT GetPos() { ... }를 직접 정의.
    // C에서는 struct 내부에 함수 정의 불가.
    // 대신 아래쪽에서 inline 함수로 바로 정의하되, 
    // 구조 상으로 여기에 주석 달아놓고 실제 정의는 뒤에서 곧바로 한다.
public:
    // CMouse(), ~CMouse()도 원래 여기 선언만 하고 cpp에서 정의하거나 inline 정의 가능
    // 여기서는 아래에 대응하는 함수를 전역으로 선언
};

#undef class
#undef public

// 여기서 inline 함수로 GetPos() 정의
static inline POINT CMouse_GetPos(void)
{
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(g_hWnd, &pt);
    return pt;
}

// 생성자/소멸자 대응 함수
void CMouse_Construct(CMouse* pThis);
void CMouse_Destruct(CMouse* pThis);

#ifdef __cplusplus
}
#endif
