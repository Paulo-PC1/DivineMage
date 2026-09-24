#pragma once
#include "raylib.h"
#include "core/animation/animation.h"

struct Player {
    float x; // Posição do jogador no eixo x
    float y; // Posição do jogador no eixo y
    Vector2 oldPos; // Posição antiga do jogador
    float speed; // Velocidade do jogador
    Texture2D texture; // Textura do jogador
};

Player initPlayer(float x, float y, float speed);
void updatePlayer(Player &player, float dt);
void drawPlayer(const Player &player, const Animation &anim);
void unloadPlayer(Player &player);
