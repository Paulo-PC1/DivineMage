#pragma once
#include "rooms/room/room.hpp"

class Player;

// Guarda as 3 salas e sabe qual está ativa
class World {
public:
    World();

    bool load();       // carrega os 3 mapas e monta inimigos, portas e itens de cada sala
    void unload();

    void update(float dt, Player &player);  // atualiza a sala atual e troca de sala ao tocar numa porta
    void draw() const;

    Room &getCurrentRoom();                 // a GameScreen precisa das paredes e dos projéteis
    bool isBossDefeated() const;            // dispara a tela de créditos

private:
    void changeRoom(int index, Vector2 spawn, Player &player);

    static constexpr int ROOM_COUNT = 3;
    Room _rooms[ROOM_COUNT];   // array simples: não exige copiar a Room
    int _currentRoom;
};