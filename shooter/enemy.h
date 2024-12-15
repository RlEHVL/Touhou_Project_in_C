#pragma once

#include "utils.h"

typedef struct {
    Vec2d position;
    Vec2d velocity;
    int health;
    int alive;
} Enemy;

void initEnemy(Enemy* enemy, Vec2d position, Vec2d velocity) {
    enemy->position = position;
    enemy->velocity = velocity;
    enemy->health = 100;
    enemy->alive = 1;
}

void updateEnemy(Enemy* enemy) {
    if (!enemy->alive) return;
    enemy->position.x += enemy->velocity.x;
    enemy->position.y += enemy->velocity.y;
}

void damageEnemy(Enemy* enemy, int damage) {
    enemy->health -= damage;
    if (enemy->health <= 0) {
        enemy->alive = 0;
    }
}
