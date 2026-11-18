#pragma once
#include "entities/entity/entity.hpp"

class Projectile : public Entity {
public:
    // center = ponto de origem do tiro. O próprio projétil calcula o canto do hitbox
    // (o chamador não precisa se preocupar com offsets)
    Projectile(Vector2 center, Vector2 direction, float speed, int damage,
               float lifetime, float radius, Color color);  // color: tiro do jogador x tiro inimigo

    void update(float dt, const std::vector<Rectangle> &walls) override; // anda, gasta vida, morre na parede
    void draw() const override;                                          // círculo; sprite depois da entrega

    bool isAlive() const;   // a Room remove os que devolvem false
    void destroy();         // quando acerta alguém
    int getDamage() const;

private:
    Vector2 _direction;     // já normalizada
    float _speed;
    int _damage;
    float _lifetimeLeft;
    float _radius;          // também define o tamanho do hitbox
    Color _color;
    bool _alive;
};