#include "BulletMap.h"
#include <stdbool.h>

/*
    *
    * 제작:동필
    * 도움이:지피티
*/

bool Map_FindBulletList(BulletMap* map, OBJTYPE type, list_CObj** ppList) {
    for (int i = 0; i < map->count; i++) {
        if (map->entries[i].key == type) {
            *ppList = map->entries[i].value;
            return true;
        }
    }
    return false;
}

void Map_InsertBulletList(BulletMap* map, OBJTYPE type, list_CObj* pList) {
    if (map->count < 100) {
        map->entries[map->count].key = type;
        map->entries[map->count].value = pList;
        map->count++;
    }
}
