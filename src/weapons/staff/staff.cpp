// DivineMage - Shooter/src/weapons/staff/staff.cpp
#include "weapons/staff/staff.hpp" // Inclui cabeçalho da classe

// Constantes que só este arquivo usa (o namespace sem nome as esconde do resto do projeto)
namespace {
    constexpr float COOLDOWN = 0.35f;            // Segundos entre um tiro e outro
    constexpr float PROJECTILE_SPEED = 260.0f;   // Velocidade do projétil (pixels por segundo)
    constexpr int   DAMAGE = 10;                 // Dano de cada projétil
    constexpr float PROJECTILE_LIFETIME = 1.2f;  // Segundos até o projétil sumir sozinho
    constexpr float PROJECTILE_RADIUS = 4.0f;    // Raio do projétil (define também o tamanho do hitbox)
}

// Construtor: a BASE (Weapon) vem primeiro na lista de inicialização
Staff::Staff() :
    Weapon(COOLDOWN), // Informa o cooldown ao construtor da classe base
    _projectileSpeed(PROJECTILE_SPEED),
    _damage(DAMAGE),
    _projectileLifetime(PROJECTILE_LIFETIME)
{
    // Nada a fazer aqui: tudo já foi inicializado na lista acima
}

// Tenta atirar: devolve true se o tiro saiu, false se a arma ainda está em cooldown
bool Staff::shoot(Vector2 origin, Vector2 direction, std::vector<Projectile> &projectiles)
{
    if (!canShoot()) // Método da classe base: o contador do cooldown já zerou?
    {
        return false; // Ainda em cooldown, não atira
    }

    // Cria o projétil direto dentro do vetor (origin é o CENTRO do projétil)
    projectiles.emplace_back(origin, direction, _projectileSpeed, _damage, _projectileLifetime, PROJECTILE_RADIUS, SKYBLUE);

    startCooldown(); // Método da classe base: reinicia o contador do cooldown

    return true; // O tiro saiu
}