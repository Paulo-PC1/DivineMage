#pragma once
#include "rooms/tilemap/tilemap.hpp"
#include "rooms/door/door.hpp"
#include "entities/enemy/enemy.hpp"
#include "entities/mini_boss/mini_boss.hpp"
#include "entities/pickup/pickup.hpp"
#include "weapons/projectile/projectile.hpp"
#include <vector>
#include <string>

class Player;

class Room {
public:
    Room();                                  // zera tudo (texturas inclusive): permite o array do World
    ~Room();                                 // chama unload()
    Room(const Room &) = delete;
    Room &operator=(const Room &) = delete;

    bool load(const std::string &mapPath, const std::string &tilesetPath); // mapa + texturas dos inimigos
    void unload();

    // Montagem (chame DEPOIS do load: os inimigos apontam para as texturas carregadas)
    // Posições de spawn = canto superior esquerdo do sprite, igual ao construtor do Player
    void addEnemy(float x, float y);
    void addBoss(float x, float y);
    void addDoor(const Door &door);
    void addLoot(const Pickup &loot);        // loot fixo: só aparece quando a sala é limpa
    void setPlayerSpawn(Vector2 spawn);

    void update(float dt, Player &player);
    void draw() const;

    const std::vector<Rectangle> &getCollisionRects() const;  // paredes + portas trancadas
    std::vector<Projectile> &getPlayerProjectiles();          // o Player::shoot adiciona aqui
    const Door *getDoorTouching(const Rectangle &playerHitbox) const; // nullptr se nenhuma
    Vector2 getPlayerSpawn() const;
    int getPixelWidth() const;
    int getPixelHeight() const;
    bool isCleared() const;
    bool isBossDefeated() const;

private:
    // Room::update é grande: dividi em etapas pequenas
    void updateEnemies(float dt, Player &player);      // alvo, update, attack, dano de contato
    void updateProjectiles(float dt, Player &player);  // movimento e acertos dos dois vetores
    void updateLoot(Player &player);                   // tryCollect, só se a sala estiver limpa
    void checkCleared();                               // todos mortos → limpa, destranca portas
    void rebuildCollisionRects();

    TileMap _tilemap;
    Texture2D _enemyTexture;
    Texture2D _bossTexture;
    std::vector<Enemy> _enemies;               // só inimigos comuns (evita slicing)
    std::vector<MiniBoss> _bosses;             // 0 ou 1; nunca apagado (isBossDefeated lê daqui)
    std::vector<Door> _doors;
    std::vector<Pickup> _loot;
    std::vector<Projectile> _playerProjectiles;
    std::vector<Projectile> _enemyProjectiles;
    std::vector<Rectangle> _collisionRects;
    Vector2 _playerSpawn;
    bool _cleared;                             // persiste: a sala não "respawna" (RF003)
};