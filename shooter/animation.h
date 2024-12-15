#pragma once

#include "player.h"
#include "texture.h"

typedef struct {
    Vec2d position;
    Vec2d direction;
    int frame;
} Animation;

typedef struct {
    Animation base;
    SDL_Rect clip;
} PlayerDeadAnimation;

void initPlayerDeadAnimation(PlayerDeadAnimation* anim, Vec2d position) {
    anim->base.position = position;
    anim->base.frame = 0;
    anim->clip = (SDL_Rect){25, 25, 32, 32};
}

int updatePlayerDeadAnimation(PlayerDeadAnimation* anim) {
    if (anim->base.frame >= 60) return 0;
    anim->base.frame++;
    return 1;
}

void renderPlayerDeadAnimation(PlayerDeadAnimation* anim, Texture* texture) {
    textureSetAlpha(texture, (1.0 - (anim->base.frame / 8.0)) * 255);
    renderTexture(texture, anim->base.position.x, anim->base.position.y, &anim->clip, 
                  anim->clip.w + anim->base.frame * 32, 
                  anim->clip.h + anim->base.frame * 32);
    textureSetAlpha(texture, 255);
}
