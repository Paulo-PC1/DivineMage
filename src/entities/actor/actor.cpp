#include "entities/actor/actor.hpp" // Inclui o cabeçalho da classe Actor, que herda de Entity e adiciona atributos específicos para atores, como velocidade e saúde máxima

Actor::Actor(float x, float y, float hitboxOffSetX, float hitboxOffSetY, float hitboxWidth, float hitboxHeight, float speed, int maxHealth)
    : Entity(x, y, hitboxOffSetX, hitboxOffSetY, hitboxWidth, hitboxHeight), // Chama o construtor da classe base Entity com os parametros fornecidos
        _speed(speed), // Inicializa o atributo de velocidade com o valor fornecido
        _health(maxHealth), // Inicializa a vida atual com a vida máxima fornecida
        _maxHealth(maxHealth), // Inicializa a vida máxima com o valor fornecido
        _invulnerabilityDuration(0.0f), // Inicializa a duração da invulnerabilidade com 1 segundo
        _invulnerabilityTimer(0.0f) // Inicializa o temporizador da invulnerabilidade com 0 segundos
{
    // Construtor da classe Actor, que herda de Entity e adiciona atributos específicos
}        

void Actor::takeDamage(int amount) {
        
    if(!isInvulnerable())
    {
        _health -= amount; // Reduz a vida pelo valor recebido
        if(_health < 0)
        {
            _health = 0; // Vida não abaixa de zero
        }
        _invulnerabilityTimer = _invulnerabilityDuration; // Reinicia o temporizador da invulnerabilidade
    }   
   
}

void Actor::heal(int amount)
{
    _health += amount; // Aumanta a vida base no valor ecebido
    
    if(_health > _maxHealth)
    {
        _health = _maxHealth; // Vida não ultrapassa a vida máxima
    }
}

bool Actor::isDead() const
{
    return _health <= 0; // Retorna true se a vida for menor ou igual a zero, indicando que o ator está morto
}

bool Actor::isInvulnerable() const
{
    return _invulnerabilityTimer > 0.0f; // Retorna true se o temporizador da invulnerabilidade for maior que zero, indicando que o ator está invulnerável
}

int Actor::getHealth() const
{
    return _health; // Retorna vida atual
}

int Actor::getMaxHealth() const
{
    return _maxHealth; // Retorna vida máxima
}

bool Actor::collidesWithWalls(const std::vector<Rectangle> &walls) const
{
   Rectangle hitbox =  getHitbox(); // Pega a hitbox 1 unica vez na posição atual
   
   for( const Rectangle &wall : walls)  // Percorre o retângulo da parede
   {
        if(CheckCollisionRecs(hitbox, wall)) // Se hitbox sobrepor a parede
        { 
            return true; // Retorna true (não precisa verificar outras)
        }
   }
   
   return false;  // Percorreu todas e nenhuma bateu
}

void Actor::moveWithCollision(Vector2 displacement, const std::vector<Rectangle> &walls)
{
    float oldPosX = _x; // Guarda a posiçãp antiga do x
    _x += displacement.x; // Move o x pela quantidade de deslocamento
    if(collidesWithWalls(walls)) // Se colidir com a parede
    {
        _x = oldPosX; // Volta para a posição antiga do x
    }
    
    float oldPosY = _y; // Guarda a posiçãp antiga do y
    _y += displacement.y; // Move o y pela quantidade de deslocamento
    if(collidesWithWalls(walls)) // Se colidir com a parede
    {
        _y = oldPosY; // Volta para a posição antiga do y
    }
}

void Actor::updateInvulnerability(float dt)
{
    if(_invulnerabilityTimer > 0.0f) // Se o temporizador da invulnerabilidade for maior que zero
    {
        _invulnerabilityTimer -= dt; // Reduz o temporizador pelo delta time
        if(_invulnerabilityTimer < 0.0f) // Se o temporizador ficar menor que zero
        {
            _invulnerabilityTimer = 0.0f; // Zera o temporizador
        }
    }
}
