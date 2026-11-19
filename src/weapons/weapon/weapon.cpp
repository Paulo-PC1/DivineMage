// DivineMage - Shooter/src/weapons/weapon/weapon.cpp
#include "weapons/weapon/weapon.hpp" // Inclui cabeçalho da classe

Weapon::Weapon(float cooldown) : _cooldown(cooldown), _cooldownTimer(0.0f) 
{
    
}

void Weapon::update(float dt)
{
    if (_cooldownTimer > 0.0f)
    {
        _cooldownTimer -= dt;
        if (_cooldownTimer < 0.0f)
        {
            _cooldownTimer = 0.0f; // Garante que o temporizador não fique negativo
        }
    }
}

bool Weapon::canShoot() const
{
    return _cooldownTimer <= 0.0f; // Retorna true se o temporizador de cooldown for menor ou igual a zero, indicando que a arma pode atirar
}

void Weapon::startCooldown() 
{
    _cooldownTimer = _cooldown; // Reinicia o temporizador de cooldown com o valor do cooldown da arma
}