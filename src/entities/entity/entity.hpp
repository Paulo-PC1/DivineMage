//DivineMage - Shooter/src/entities/entity/entity.hpp
#pragma once

#include "raylib.h"
#include <vector>

class Entity {
  
public:

    //Construtor da classe Entity
    Entity(float x, float y, float hitboxOffSetX, float hitboxOffSetY, float hitboxWidth, float hitboxHeight);
    
    //Destrutor da classe Entity
    virtual ~Entity() = default;
    
    virtual void update(float dt, const std::vector<Rectangle> &walls) = 0; // Método virtual puro para atualizar a entidade, deve ser implementado nas classes derivadas
    
    virtual void draw() const = 0; // Método virtual puro para desenhar a entidade, deve ser implementado nas classes derivadas
    
    Rectangle getHitbox() const; // Retorna a hitbox da entidade 
    
    Vector2 getCenter() const; // Retorna o centro da entidade 
    
    float getX() const; // Retorna a posição X da entidade
    float getY() const; // Retorna a posição Y da entidade
    void setPosition(float x, float y); // Define a posição da entidade
    
protected:
    
    //Atributos da classe 
    float _x; // Define a posição X da entidade
    float _y; // Define a posição Y da Entidade
    float _hitboxOffSetX; // Define o deslocamento da hitbox em relação a posição X
    float _hitboxOffSetY; // Define o deslocamento da hitbox em relação a posição Y
    float _hitboxWidth; // Define a largura da hitbox
    float _hitboxHeight; // Define a altura da hitbox
};

