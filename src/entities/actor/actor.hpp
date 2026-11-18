//DivineMage - Shooter/src/entities/actor/actor.hpp
#pragma once 

#include "entities/entity/entity.hpp"

class Actor : public Entity {
    
public:
    
    // Construtor da classe Actor, que herda de Entity e adiciona atributos específicos para atores, como velocidade e saúde máxima
    Actor(float x, float y, float hitboxOffSetX, float hitboxOffSetY, float hitboxWidth, float hitboxHeight, float speed, float maxHealth);
    
    void takeDamage(int amount); // Método que ignora se estiver invulnerável; senão reduz a vida
    void heal(int amount); // Método que aumenta a vida, sem ultrapassar a vida máxima
    bool idDead() const; // Método para retornar se ator esta morto ou não
    bool isInvulnerable() const; // Método para retornar se ator esta invulnerável ou não (pisca quando toma dano)
    int getHealth() const; // Método para retornar a vida atual do ator
    int getMaxHealth() const; // Método para retornar a vida máxima do ator

protected:

    // Atributos da classe Actor
    bool collidesWithWalls(const std::vector<Rectangle> &walls) const; // Método para verificar colisão com paredes, sem cópias e sem modificação
    void moveWithCollision(Vector2 displacement, const std::vector<Rectangle> &walls); // Método para mover o ator com colisão, sem cópias e sem modificação
    void updateInvulnerability(float dt); // Método para atualizar o estado de invulnerabilidade do ator, sem cópias e sem modificação
    
    float _speed; // Atributo que define a velocidade
    int _health; // Atributo que define a vida
    int _maxHealth; // Atributo que define a vida máxima
    float _invulnerabilityDuration; // Atributo que define a duração da invulnerabilidade
    float _invulnerabilityTimer; // Atributo que define o temporizador da invulnerabilidade
};