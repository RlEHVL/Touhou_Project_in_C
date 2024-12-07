#include "BackGround.h"
#include <stdlib.h>

// 상수 정의 (헤더 파일 또는 별도 파일에서 정의 필요)
#define WINCX 800
#define WINCY 600

// 함수 구현
void CBackGround_Initialize(CBackGround* self) {
    // 초기화 작업
    self->m_pMapBmp = MapBmp_Create(); // 가상 MapBmp 생성
}

int CBackGround_Progress(CBackGround* self) {
    // 로직 처리
    return 0;
}

void CBackGround_Render(CBackGround* self, HDC hdc) {
    if (self->m_pMapBmp) {
        BitBlt(hdc,
            0, 0, WINCX, WINCY,
            MapBmp_GetMemDC(self->m_pMapBmp, "BackGround"), // GetMemDC 호출
            0, 0, SRCCOPY);
    }
}

void CBackGround_Release(CBackGround* self) {
    if (self->m_pMapBmp) {
        MapBmp_Destroy(self->m_pMapBmp); // m_pMapBmp 해제
        self->m_pMapBmp = NULL;
    }
}

// 생성자
CBackGround* CBackGround_Create() {
    CBackGround* newBackGround = (CBackGround*)malloc(sizeof(CBackGround));
    if (!newBackGround) {
        return NULL;
    }

    // 멤버 변수 초기화
    newBackGround->m_pMapBmp = NULL;

    // 함수 포인터 초기화
    newBackGround->Initialize = CBackGround_Initialize;
    newBackGround->Progress = CBackGround_Progress;
    newBackGround->Render = CBackGround_Render;
    newBackGround->Release = CBackGround_Release;

    return newBackGround;
}

// 소멸자
void CBackGround_Destroy(CBackGround* self) {
    if (self) {
        self->Release(self);
        free(self);
    }
}
