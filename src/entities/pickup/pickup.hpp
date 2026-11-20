#pragma once
#include "entities/entity/entity.hpp"
#include "potions/health_potion/health_potion.hpp"

// Poção no chão. Usada automaticamente ao encostar, se a poção permitir
class Pickup : public Entity {
public:
    Pickup(float x, float y);

    void update(float dt, const std::vector<Rectangle> &walls) override; // pode ficar vazio
    void draw() const override;                                          // não desenha se já foi coletada

    // A Room chama quando o hitbox do jogador encosta. Devolve true se aplicou e foi coletada;
    // false se a poção não pôde ser usada (vida cheia): o item continua no lugar
    bool tryCollect(Actor &target);
    bool isCollected() const;

    // A Room entrega o endereço da textura da poção (ela é a dona). Se for nullptr ou id 0, desenha um placeholder
    void setTexture(const Texture2D *texture);

private:
    HealthPotion _potion;   // composição: a poção por valor, sem ponteiro e sem delete
    bool _collected;
    const Texture2D *_texture;  // NÃO é dono: a textura pertence à Room
};
