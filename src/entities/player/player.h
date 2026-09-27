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

Player initPlayer(float x, float y, float speed); // função que inicializa o jogador
void updatePlayer(Player &player, float dt); // função que atualiza a posição do jogador de acordo com as teclas pressionadas
void drawPlayer(const Player &player, const Animation &anim); // função que desenha o jogador na tela de acordo com a animação atual
void unloadPlayer(Player &player); // função que descarrega a textura do jogador
