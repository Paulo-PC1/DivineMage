#include "entities/entity/entity.hpp"

Entity::Entity(float x, float y, float hitboxOffSetX, float hitboxOffSetY, float hitboxWidth, float hitboxHeight) :
    _x(x), _y(y), _hitboxOffSetX(hitboxOffSetX), _hitboxOffSetY(hitboxOffSetY), _hitboxWidth(hitboxWidth), _hitboxHeight(hitboxHeight) {}
    
Rectangle Entity::getHitbox() const {
    
    return {
        _x + _hitboxOffSetX, // Calcula a coordenada x do canto superior esquerdo da hitbox adicionando o deslocamento à posição x
        _y + _hitboxOffSetY, // Calcula a coordenada y do canto superior esquerdo da hitbox adicionando o deslocamento à posição y
        _hitboxWidth,        // Define a largura da hitbox
        _hitboxHeight        // Define a altura da hitbox
    };
}

Vector2 Entity::getCenter() const {
    
    Rectangle centerHitbox = getHitbox();
    return {
        centerHitbox.x + centerHitbox.width / 2.0f, // Calcula a coordenada x do centro da hitbox adicionando metade da largura à coordenada x do canto superior esquerdo
        centerHitbox.y + centerHitbox.height / 2.0f // Calcula a coordenada y do centro da hitbox adicionando metade da altura à coordenada y do canto superior esquerdo
    };
}

// Getters
float Entity::getX() const 
{ 
    return _x;  
}

float Entity::getY() const 
{
    return _y;
}

void Entity::setPosition(float x, float y) 
{
    _x = x; // Atualiza a posição x da entidade
    _y = y; // Atualiza a posição y da entidade
}