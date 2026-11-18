#pragma once
#include "entities/actor/actor.hpp"
#include "core/animation/animation.hpp"
#include "weapons/projectile/projectile.hpp"

class Enemy : public Actor {
public:
    Enemy(float x, float y, const Texture2D &texture);  // inimigo comum, valores padrão

    void update(float dt, const std::vector<Rectangle> &walls) override; // persegue _target
    void draw() const override;

    // Gancho de ataque: a Room chama a cada frame. O inimigo comum não faz nada;
    // MiniBoss (e, no futuro, atiradores) sobrescrevem
    virtual void attack(std::vector<Projectile> &projectiles);

    void setTarget(Vector2 targetPosition);  // a Room informa onde está o jogador (update não recebe o jogador)
    int getContactDamage() const;            // dano ao encostar, aplicado pela Room

protected:
    // Para o MiniBoss informar frames, hitbox, velocidade, vida e dano próprios
    Enemy(float x, float y, const Texture2D &texture, int totalFrames,
          float hitboxOffsetX, float hitboxOffsetY, float hitboxWidth, float hitboxHeight,
          float speed, int maxHealth, int contactDamage);

    Vector2 _target;       // o MiniBoss lê para mirar a rajada
    int _contactDamage;

private:
    const Texture2D *_texture;  // NÃO é dono: a textura pertence à Room
    Animation _anim;
    bool _facingLeft;
};