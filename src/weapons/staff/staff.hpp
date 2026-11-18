// DivineMage - Shooter/src/staff/staff/staff.hpp
#pragma once

#include "weapons/weapon/weapon.hpp" // Inclui a definição da classe Weapon

class Staff : public Weapon {

public:

    //Construtor da classe Staff
    Staff();
    
    bool shoot(Vector2 origin, Vector2 direction, std::vector<Projectile> &projectiles) override; // Implementação do método shoot da classe Weapon
    
private:
    
    float _projectileSpeed; // Velocidade do projétil disparado pelo cajado
    int _damage; // Dano do projétil disparado pelo cajado
    float _projectileLifetime; // Tempo de vida do projétil disparado pelo cajado
};