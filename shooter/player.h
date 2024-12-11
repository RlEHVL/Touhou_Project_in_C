// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include <stdint.h>

// 필요한 헤더 포함
#include "info.h"
#include "frame.h"

/*
    *
    * 제작:동필
    * 도움이:지피티
*/

// Forward declarations
typedef struct CPlayer CPlayer;

// Function pointer types for methods
typedef void (*InitializeFunc)(CPlayer*);
typedef int (*ProgressFunc)(CPlayer*);
typedef void (*RenderFunc)(CPlayer*, void* hdc); // Assuming HDC is a void pointer for genericity
typedef void (*ReleaseFunc)(CPlayer*);
typedef int (*HitFunc)(CPlayer*);
typedef void (*KeyCheckFunc)(CPlayer*);
typedef void (*FrameFunc)(CPlayer*);
typedef void (*DirectionFunc)(CPlayer*);
typedef void (*MotionFunc)(CPlayer*);
typedef void (*SetSceneFunc)(CPlayer*, int, int, uint32_t);
typedef void (*SkillShotFunc)(CPlayer*, int);
typedef void (*CreateBulletFunc)(CPlayer*, float, float, float, int, int);

// Player structure
struct CPlayer {
    // Data members
    INFO m_tInfo;
    INFO m_BmpInfo;
    FRAME m_tFrame;
    uint32_t m_dwState;

    float m_fSpeed;
    uint32_t m_dwKey;
    uint32_t m_dwTime;
    uint32_t m_dwShoot;
    int m_tCount[10]; // Assuming SKL_END is 10

    float m_fAngle;
    int m_iSkillNum;
    bool m_bCheck;
    bool m_bEvade;
    bool m_bView;
    char* m_strDrawID;
    int m_iSound;
    int m_iLife;

    // Additional members like m_pMapBmp, m_pBulletList, m_ptScroll etc.
    // These need to be defined as per the original C++ class

    // Function pointers
    InitializeFunc Initialize;
    ProgressFunc Progress;
    RenderFunc Render;
    ReleaseFunc Release;
    HitFunc Hit;
    KeyCheckFunc KeyCheck;
    FrameFunc Frame;
    DirectionFunc Direction;
    MotionFunc Motion;
    SetSceneFunc SetScene;
    SkillShotFunc SkillShot;
    CreateBulletFunc CreateBullet;

};

// Function declarations
CPlayer* CreatePlayer();
void DestroyPlayer(CPlayer* player);

#endif // PLAYER_H
