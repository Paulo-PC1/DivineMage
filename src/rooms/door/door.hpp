#pragma once
#include "raylib.h"

// Não é uma Entity: não anda, não tem vida. É uma área com um destino
class Door {
public:
    // closedFrame = qual frame do Door.png mostra a porta FECHADA (1 = vermelha, 2 = azul, 3 = roxa).
    // O frame 0 é sempre a porta ABERTA. Cada porta escolhe o frame que combina com a parede da sala
    Door(Rectangle area, int targetRoom, Vector2 spawnInTarget, int closedFrame = 1);

    void lock();
    void unlock();                 // a Room destranca quando o último inimigo morre
    bool isLocked() const;
    void draw() const;             // aberta e fechada têm aparências diferentes

    bool isTouching(const Rectangle &hitbox) const;  // true só se destrancada e houver contato
    Rectangle getArea() const;     // trancada, vira parede na lista de colisão da Room
    int getTargetRoom() const;
    Vector2 getSpawnInTarget() const;  // onde o jogador aparece na sala de destino

    // A Room entrega o endereço da textura da porta (ela é a dona). Se for nullptr ou id 0, desenha um placeholder
    void setTexture(const Texture2D *texture);

private:
    Rectangle _area;
    int _targetRoom;
    Vector2 _spawnInTarget;
    bool _locked;
    int _closedFrame;           // frame usado quando a porta está trancada
    const Texture2D *_texture;  // NÃO é dono: a textura pertence à Room
};
