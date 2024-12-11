// player.c

#include "player.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Forward declarations for dependent functions and types
#include "KeyMgr.h"
#include "Device.h"
#include "ObjFactory.h"
#include "Bullet.h"
#include "NormalBullet.h"
#include "GuideBullet.h"
#include "ThrustBulletA.h"
#include "BounceBullet.h"

/*
    *
    * 제작:동필
    * 도움이:지피티
*/

// Example implementations of methods

void Player_Initialize(CPlayer* player) {
    if (!player) return;

    player->m_tInfo = Info_Create(WINCX / 2, WINCY - 100, 10, 10, 2);
    player->m_BmpInfo = Info_Create(0, 0, 32, 48);
    player->m_tFrame = Frame_Create(0, 4, 0, 100);
    player->m_dwState = STATE_STAND;

    player->m_fSpeed = 5.f;
    player->m_dwKey = 0;
    player->m_dwTime = GetTickCount();
    player->m_dwShoot = GetTickCount();

    for (int i = 0; i < SKL_END; ++i) {
        player->m_tCount[i] = 50;
    }

    player->m_fAngle = 90;
    player->m_iSkillNum = NORMAL;
    player->m_tCount[GUIDED] = 200;

    player->m_bCheck = true;
    player->m_bEvade = false;
    player->m_bView = true;
    player->m_strDrawID = strdup("Player1");
    player->m_iSound = 3;
    player->m_iLife = 3;
}

int Player_Progress(CPlayer* player) {
    if (player->m_bPlay) {
        player->KeyCheck(player);
        if (player->m_dwLifeTime + 1000 < GetTickCount()) {
            player->m_bEvade = false;
            player->m_bView = true;
        }
    } else {
        if (player->m_dwLifeTime + 2000 < GetTickCount()) {
            player->m_dwLifeTime = GetTickCount();
            player->m_bPlay = true;
        }
        player->m_tInfo.fy -= 1.5f;
    }

    player->Frame(player);
    player->Direction(player);
    player->Motion(player);

    if (player->m_iLife == -1) {
        player->m_bPlay = false;
        player->m_bEvade = true;
        player->m_bView = true;
        player->m_tInfo.fy += 1.5f;
    }

    return 0;
}

void Player_Render(CPlayer* player, void* hdc) { // Assuming HDC is a generic pointer
    if (player->m_bEvade) {
        if (player->m_dwViewTime + 200 < GetTickCount()) {
            player->m_dwViewTime = GetTickCount();
            player->m_bView = !player->m_bView;
        }
    }

    if (player->m_bView) {
        // Render player sprite using TransparentBlt or equivalent in C
        // Requires handling the rendering context and bitmaps in C
    }

    for (int i = 0; i < player->m_iLife; ++i) {
        // Render life indicators
    }
}

void Player_Release(CPlayer* player) {
    if (player->m_strDrawID) {
        free(player->m_strDrawID);
        player->m_strDrawID = NULL;
    }
}

int Player_Hit(CPlayer* player) {
    player->m_dwLifeTime = GetTickCount();
    player->m_bPlay = false;
    player->m_bEvade = true;
    player->m_dwViewTime = GetTickCount();
    player->m_dwKey = 0;

    if (player->m_iLife > 0) {
        player->m_iLife--;
        player->m_tInfo.fx = WINCX / 2;
        player->m_tInfo.fy = WINCY + 100;
    } else {
        player->m_iLife--;
        return 1;
    }

    return 0;
}

void Player_KeyCheck(CPlayer* player) {
    player->m_dwKey = KeyMgr_GetKey(); // Assuming a function to get keys

    if (player->m_dwKey & KEY_UP && player->m_tInfo.fy > player->m_tInfo.fcy / 2) {
        player->m_tInfo.fy -= player->m_fSpeed;
    }
    if (player->m_dwKey & KEY_DOWN && player->m_tInfo.fy < WINCY - player->m_tInfo.fcy / 2) {
        player->m_tInfo.fy += player->m_fSpeed;
    }
    if (player->m_dwKey & KEY_LEFT && player->m_tInfo.fx > player->m_tInfo.fcx / 2 - player->m_ptScroll.x) {
        player->m_tInfo.fx -= player->m_fSpeed;
    }
    if (player->m_dwKey & KEY_RIGHT && player->m_tInfo.fx < WINCX - player->m_tInfo.fcx / 2 - player->m_ptScroll.x) {
        player->m_tInfo.fx += player->m_fSpeed;
    }

    if (player->m_dwKey & KEY_SPACE) {
        if (player->m_dwShoot + player->m_tCount[player->m_iSkillNum] < GetTickCount()) {
            player->m_dwShoot = GetTickCount();
            Device_SoundPlay(player->m_iSound, 0);
            player->SkillShot(player, player->m_iSkillNum);
        }
    }

    if (GetAsyncKeyState('Z')) {
        player->m_iBSprd = 1.f;
        player->m_fSpeed = 2.f;
    } else {
        player->m_fSpeed = 5.f;
        player->m_iBSprd = 7.5f;
    }

    if (GetAsyncKeyState('A')) {
        player->m_iSkillNum = NORMAL;
        free(player->m_strDrawID);
        player->m_strDrawID = strdup("Player1");
        player->m_iSound = 3;
    }
    if (GetAsyncKeyState('S')) {
        player->m_iSkillNum = SPREAD;
        free(player->m_strDrawID);
        player->m_strDrawID = strdup("Player2");
        Device_SoundStop(3);
        player->m_iSound = 2;
    }
    if (GetAsyncKeyState('D')) {
        player->m_iSkillNum = GUIDED;
        free(player->m_strDrawID);
        player->m_strDrawID = strdup("Player3");
        player->m_iSound = 3;
    }
    if (GetAsyncKeyState('C')) {
        if (player->m_bEvade) {
            player->m_bEvade = false;
            player->m_bView = true;
        } else {
            player->m_bEvade = true;
            player->m_dwViewTime = GetTickCount();
        }
    }
}

void Player_Frame(CPlayer* player) {
    if (player->m_dwTime + player->m_tFrame.dwTime < GetTickCount()) {
        player->m_dwTime = GetTickCount();
        player->m_tFrame.iStart++;

        if (player->m_tFrame.iStart >= player->m_tFrame.iLast) {
            if (player->m_dwState & STATE_STAND)
                player->m_tFrame.iStart = 0;
            else
                player->m_tFrame.iStart = 3;

            if (player->m_dwState != STATE_STAND)
                player->m_dwState = STATE_STAND;
        }
    }
}

void Player_Direction(CPlayer* player) {
    if (!(KEY_RIGHT & KEY_LEFT & player->m_dwKey))
        player->m_dwState = STATE_STAND;

    if (player->m_dwKey & KEY_LEFT)
        player->m_dwState = STATE_WALKL;

    if (player->m_dwKey & KEY_RIGHT)
        player->m_dwState = STATE_WALKR;
}

void Player_Motion(CPlayer* player) {
    if (player->m_dwState & STATE_STAND)
        Player_SetScene(player, 4, 0, 100);

    if (player->m_dwState & STATE_WALKL)
        Player_SetScene(player, 7, 1, 100);

    if (player->m_dwState & STATE_WALKR)
        Player_SetScene(player, 7, 2, 100);
}

void Player_SetScene(CPlayer* player, int _last, int _scene, uint32_t _time) {
    if (player->m_tFrame.iScene != _scene)
        player->m_tFrame.iStart = 0;

    player->m_tFrame.iLast = _last;
    player->m_tFrame.iScene = _scene;
    player->m_tFrame.dwTime = _time;
}

void Player_SkillShot(CPlayer* player, int _id) {
    switch (_id) {
        case NORMAL:
            Player_CreateBullet(player, 0, -20, player->m_fAngle, PBL_NORMAL, 0);
            Player_CreateBullet(player, 7, -15, player->m_fAngle - player->m_iBSprd, PBL_NORMAL, 0);
            Player_CreateBullet(player, -7, -15, player->m_fAngle + player->m_iBSprd, PBL_NORMAL, 0);
            break;
        case SPREAD:
            Player_CreateBullet(player, 0, -20, player->m_fAngle, PBL_NORMAL, 1);
            Player_CreateBullet(player, 3, -18, player->m_fAngle - player->m_iBSprd * 1.3f, PBL_NORMAL, 1);
            Player_CreateBullet(player, -3, -18, player->m_fAngle + player->m_iBSprd * 1.3f, PBL_NORMAL, 1);
            Player_CreateBullet(player, 7, -15, player->m_fAngle - player->m_iBSprd * 2.8f, PBL_NORMAL, 1);
            Player_CreateBullet(player, -7, -15, player->m_fAngle + player->m_iBSprd * 2.8f, PBL_NORMAL, 1);
            Player_CreateBullet(player, 10, -13, player->m_fAngle - player->m_iBSprd * 4.5f, PBL_NORMAL, 1);
            Player_CreateBullet(player, -10, -13, player->m_fAngle + player->m_iBSprd * 4.5f, PBL_NORMAL, 1);
            Player_CreateBullet(player, 10, -13, player->m_fAngle - player->m_iBSprd * 7, PBL_NORMAL, 1);
            Player_CreateBullet(player, -10, -13, player->m_fAngle + player->m_iBSprd * 7, PBL_NORMAL, 1);
            break;
        case GUIDED:
            Player_CreateBullet(player, 3, 3, 45, PBL_BOUNCE, 0);
            Player_CreateBullet(player, -3, 3, 135, PBL_BOUNCE, 0);
            Player_CreateBullet(player, 1, 5, 60, PBL_BOUNCE, 0);
            Player_CreateBullet(player, -1, 5, 120, PBL_BOUNCE, 0);
            Player_CreateBullet(player, 5, 0, 30, PBL_GUIDE, 0);
            Player_CreateBullet(player, -5, 0, 150, PBL_GUIDE, 0);
            break;
        case SKL_A:
            break;
        case SKL_B:
            break;
        case SKL_C:
            break;
        case SKL_END:
            break;
        default:
            break;
    }
}

void Player_CreateBullet(CPlayer* player, float _x, float _y, float _angle, int _type, int _typenum) {
    _x += player->m_tInfo.fx;
    _y += player->m_tInfo.fy;

    // Implement bullet creation logic here
    // Since C doesn't have templates, you might need separate functions for each bullet type
    // For example:
    // if (_type == PBL_NORMAL) {
    //     CreateNormalBullet(_x, _y, _angle, _typenum);
    // }
    // else if (_type == PBL_GUIDE) {
    //     CreateGuideBullet(_x, _y, _angle, _typenum);
    // }
    // ...
}

CPlayer* CreatePlayer() {
    CPlayer* player = (CPlayer*)malloc(sizeof(CPlayer));
    if (!player) return NULL;

    // Initialize members to zero or defaults
    memset(player, 0, sizeof(CPlayer));

    // Assign function pointers
    player->Initialize = Player_Initialize;
    player->Progress = Player_Progress;
    player->Render = Player_Render;
    player->Release = Player_Release;
    player->Hit = Player_Hit;
    player->KeyCheck = Player_KeyCheck;
    player->Frame = Player_Frame;
    player->Direction = Player_Direction;
    player->Motion = Player_Motion;
    player->SetScene = Player_SetScene;
    player->SkillShot = Player_SkillShot;
    player->CreateBullet = Player_CreateBullet;

    // Call initialize
    player->Initialize(player);

    return player;
}

void DestroyPlayer(CPlayer* player) {
    if (!player) return;

    player->Release(player);
    free(player);
}
