#pragma once

class Player;  // declaração antecipada

// Sem atributos: lê o jogador a cada frame. Desenhado FORA do BeginMode2D
class Hud {
public:
    void draw(const Player &player) const;  // só a vida
};