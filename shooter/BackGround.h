#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Obj.h"
#include <windows.h>

// CBackGround 구조체 정의
typedef struct _CBackGround {
    CObj base; // CObj를 상속하는 것처럼 사용
    void (*Initialize)(struct _CBackGround*); // 함수 포인터
    int (*Progress)(struct _CBackGround*);
    void (*Render)(struct _CBackGround*, HDC hdc);
    void (*Release)(struct _CBackGround*);
} CBackGround;

// 생성자 및 소멸자 함수
CBackGround* CBackGround_Create();
void CBackGround_Destroy(CBackGround*);

#endif // BACKGROUND_H
