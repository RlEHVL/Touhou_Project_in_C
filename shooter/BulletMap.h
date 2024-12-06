#ifndef BULLETMAP_H
#define BULLETMAP_H

#include "List.h" // list_CObj 관련 정의 포함
#include "CObj.h" // OBJTYPE 정의 포함

typedef struct MapEntry {
    OBJTYPE key;               // 키 (탄환 유형)
    list_CObj* value;          // 값 (탄환 리스트)
} MapEntry;

typedef struct {
    MapEntry entries[100];     // 최대 100개의 엔트리 지원
    int count;                 // 현재 엔트리 개수
} BulletMap;

// 함수 선언
bool Map_FindBulletList(BulletMap* map, OBJTYPE type, list_CObj** ppList);
void Map_InsertBulletList(BulletMap* map, OBJTYPE type, list_CObj* pList);

#endif // BULLETMAP_H
