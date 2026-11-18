#pragma once
#include "raylib.h"

// Não é uma Entity: não anda, não tem vida. É uma área com um destino
class Door {
public:
    Door(Rectangle area, int targetRoom, Vector2 spawnInTarget);

    void lock();
    void unlock();                 // a Room destranca quando o último inimigo morre
    bool isLocked() const;
    void draw() const;             // aberta e fechada têm aparências diferentes

    bool isTouching(const Rectangle &hitbox) const;  // true só se destrancada e houver contato
    Rectangle getArea() const;     // trancada, vira parede na lista de colisão da Room
    int getTargetRoom() const;
    Vector2 getSpawnInTarget() const;  // onde o jogador aparece na sala de destino

private:
    Rectangle _area;
    int _targetRoom;
    Vector2 _spawnInTarget;
    bool _locked;
};