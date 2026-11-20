#pragma once
#include "raylib.h"

class Player;  // declaração antecipada

// Lê o jogador a cada frame e desenha a vida. Desenhado FORA do BeginMode2D
class Hud {
public:
    Hud();                                  // carrega o ícone do coração (se o PNG existir)

    Hud(const Hud &) = delete;              // copiar duplicaria o id da textura
    Hud &operator=(const Hud &) = delete;

    void unload();                          // descarrega a textura (a GameScreen chama, igual ao Player)
    void draw(const Player &player) const;  // ícone de coração + barra de vida

private:
    Texture2D _heartTexture;                // PLACEHOLDER: sprites/hud/heart.png (id 0 = usa um coração desenhado com formas)
};
