#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// 함수 가정 (OBJTYPE, CObj, CBullet, CBridge, CBullet_Bridge, CThrustBulletA 등)

// 가정: CMonster_Bridge 구조체 정의
typedef struct _CMonster_Bridge {
    int m_iPhase;
    DWORD m_dwCoolTime;
    struct CObj* m_pTarget;
    // map<OBJTYPE, list<CObj*>>* m_pBulletList;
    // C에서는 map과 list를 별도 자료구조로 관리해야 함.
    void* m_pBulletList; // 포인터로 가정. 실제로는 map 관련 C 구조체
} CMonster_Bridge;

// 가정: 필요한 외부 함수 (원래 C++ 멤버 함수를 C 전역 함수로 대체)
extern bool Map_FindBulletList(void* pMap, OBJTYPE type, list_CObj** ppList);
extern void Map_InsertBulletList(void* pMap, OBJTYPE type, list_CObj* pList);

extern CBridge* CreateBridgeFunc(); // C에서 템플릿대신 함수포인터로 Bridge 생성 
extern CObj* CObjFactory_CreateCBullet(float x, float y, CBridge* pBridge);

extern void CObj_SetPos(CObj* pObj, float x, float y);
extern void CObj_Initialize(CObj* pObj);

extern void CBridge_SetAngle(CBridge* pBridge, float angle);
extern void CBullet_Bridge_SetType(CBridge* pBridge, int typeNum);
extern void CBullet_Bridge_SetSpeed(CBridge* pBridge, float speed);
extern CBridge* CObj_GetBridge(CObj* pObj);

extern bool CObj_IsActive(CObj* pObj);
extern void CObj_SetActive(CObj* pObj, bool active);

extern void CThrustBulletA_SetTarget(CBridge* pBridge, CObj* pTarget);
extern void CThrustBulletA_SetTime(CBridge* pBridge, int time);

// 원본 코드에서 template <typename T> void CMonster_Bridge::CreateBullet(...) 부분
// C로 변환: T 대신 CreateBridgeFunc 함수포인터를 받아 동일한 Bridge 생성
void CMonster_Bridge_CreateBullet(
    CMonster_Bridge* pThis,
    CBridge* (*CreateBridgeFunc)(), // T 대체 : 브릿지 객체를 생성하는 함수포인터
    float _x, float _y, float _angle, OBJTYPE _type, int _time, float _speed, int _typenum)
{
    list_CObj* pObjList = NULL;
    bool found = Map_FindBulletList(pThis->m_pBulletList, _type, &pObjList);

    if (!found) {
        // 리스트 없음: 새로 만든다.
        CBridge* pBridge = CreateBridgeFunc();
        CBridge_SetAngle(pBridge, _angle);
        CBullet_Bridge_SetType(pBridge, _typenum);

        CObj* pBullet = CObjFactory_CreateCBullet(_x, _y, pBridge);
        CObj_SetActive(pBullet, true);

        if (_speed != 0.f) {
            CBullet_Bridge_SetSpeed(CObj_GetBridge(pBullet), _speed);
        }
        if (_type == ABL_THRUST) {
            CThrustBulletA_SetTarget(CObj_GetBridge(pBullet), pThis->m_pTarget);
            CThrustBulletA_SetTime(CObj_GetBridge(pBullet), _time);
        }

        // 새로운 리스트를 만들어 삽입
        list_CObj* newList = create_list_CObj(); // 가상의 리스트 생성 함수
        list_CObj_push_back(newList, pBullet);

        Map_InsertBulletList(pThis->m_pBulletList, _type, newList);
    } else {
        // 이미 해당 타입의 리스트 있음
        // 비활성화된 탄환 재활용 시도
        bool reused = false;
        list_CObj_iterator it = list_CObj_begin(pObjList);
        for (; !list_CObj_end(it, pObjList); list_CObj_next(&it)) {
            CObj* pBullet = list_CObj_get(it);
            if (!CObj_IsActive(pBullet)) {
                CObj_SetActive(pBullet, true);
                CObj_SetPos(pBullet, _x, _y);
                CBullet_Bridge_SetType(CObj_GetBridge(pBullet), _typenum);
                CObj_Initialize(pBullet);

                CBridge_SetAngle(CObj_GetBridge(pBullet), _angle);
                if (_speed != 0.f) {
                    CBullet_Bridge_SetSpeed(CObj_GetBridge(pBullet), _speed);
                }
                if (_type == ABL_THRUST) {
                    CThrustBulletA_SetTime(CObj_GetBridge(pBullet), _time);
                }
                reused = true;
                break;
            }
        }

        if (!reused) {
            // 재활용할 탄환 없음. 새로 생성
            CBridge* pBridge = CreateBridgeFunc();
            CBridge_SetAngle(pBridge, _angle);
            CBullet_Bridge_SetType(pBridge, _typenum);

            CObj* pBullet = CObjFactory_CreateCBullet(_x, _y, pBridge);
            CObj_SetActive(pBullet, true);
            if (_speed != 0.f) {
                CBullet_Bridge_SetSpeed(CObj_GetBridge(pBullet), _speed);
            }
            if (_type == ABL_THRUST) {
                CThrustBulletA_SetTarget(CObj_GetBridge(pBullet), pThis->m_pTarget);
                CThrustBulletA_SetTime(CObj_GetBridge(pBullet), _time);
            }

            list_CObj_push_back(pObjList, pBullet);
        }
    }
}
