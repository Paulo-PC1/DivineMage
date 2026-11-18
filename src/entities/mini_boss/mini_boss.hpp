#pragma once
#include "entities/enemy/enemy.hpp"

class MiniBoss : public Enemy {
public:
    MiniBoss(float x, float y, const Texture2D &texture);  // sprite 64x64, mais vida e hitbox maior

    void update(float dt, const std::vector<Rectangle> &walls) override;  // Enemy::update (perseguir) + conta o cooldown
    void attack(std::vector<Projectile> &projectiles) override;           // rajada radial quando o cooldown zera

private:
    float _attackCooldown;      // intervalo entre rajadas
    float _attackTimer;         // tempo que falta para a próxima
    int _projectilesPerBurst;   // quantos tiros no anel (ex: 8)
    float _projectileSpeed;
    int _projectileDamage;
    float _projectileLifetime;
};