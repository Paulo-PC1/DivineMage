// DivineMage - Shooter/src/weapons/projectile/projectile.cpp
#include "weapons/projectile/projectile.hpp" // Inclusão do cabeçalho da classe
#include "raymath.h" // Inclui a biblioteca Raymath para operações matemáticas, como normalização de vetores e cálculo de comprimento de vetores

Projectile::Projectile(Vector2 center, Vector2 direction, float speed, int damage, float lifetime, float radius, Color color)
    : Entity(center.x - radius, center.y - radius, 0, 0, radius * 2, radius * 2), 
    _direction(Vector2Normalize(direction)),
    _speed(speed),
    _damage(damage),
    _lifetimeLeft(lifetime),
    _radius(radius),
    _color(color),
    _alive(true) 
{
    
}

void Projectile::update(float dt, const std::vector<Rectangle> &walls) {
    if (!_alive) return; // Projétil morto não se atualiza

    // Atualiza a posição do projétil
    _x += _direction.x * _speed * dt;
    _y += _direction.y * _speed * dt;

    // Atualiza o tempo de vida restante
    _lifetimeLeft -= dt;
    if (_lifetimeLeft <= 0) {
        _alive = false; // O projétil morre quando o tempo de vida acaba
        return;
    }

    // Verifica colisão com paredes
    Rectangle hitbox = getHitbox(); // Pega o hitbox uma vez, na posição já atualizada
    for (const Rectangle &wall : walls) {
        if (CheckCollisionRecs(hitbox, wall)) {
            _alive = false; // O projétil morre ao colidir com uma parede
            return;
        }
    }
}

void Projectile::draw() const {
    if(!_alive)
    {
        return;
    }
    DrawCircleV(getCenter(), _radius, _color);
}

bool Projectile::isAlive() const {
    return _alive;
}

void Projectile::destroy(){
    _alive = false;
}

int Projectile::getDamage() const {
    return _damage;
}