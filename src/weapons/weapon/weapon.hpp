// DivineMage - Shooter/src/weapons/weapon/weapon.hpp
#pragma once

#include "raylib.h" // Inclui a biblioteca Raylib para manipulação de gráficos e entrada
#include "weapons/projectile/projectile.hpp" // Inclui a definição da classe Projectile
#include <vector> // Inclui a biblioteca padrão de vetores do C++

class Weapon {

public: 

    //Construtor da classe Weapon
    explicit Weapon(float cooldown);
    
    // Destrutor virtual padrão
    virtual ~Weapon() = default;
    
    
    void update(float dt); // Atualiza o estado da arma, incluindo o cooldown e a atualização dos projéteis
    bool canShoot() const; // Verifica se a arma pode atirar (se o cooldown terminou)
    
    virtual bool shoot(Vector2 origin, Vector2 direction, std::vector<Projectile> &projectiles) = 0; // Método virtual puro para atirar, deve ser implementado pelas subclasses

protected:
    
    void startCooldown(); // Inicia o cooldown da arma

    float _cooldown; // Tempo de recarga da arma
    float _cooldownTimer; // Tempo desde o último disparo    
};
