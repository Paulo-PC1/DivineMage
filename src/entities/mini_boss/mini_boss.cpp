// DivineMage - Shooter/src/entities/mini_boss/mini_boss.cpp
#include "entities/mini_boss/mini_boss.hpp" // Inclui o cabeçalho da classe MiniBoss
#include <cmath> // cosf e sinf

// Constantes do chefe (o namespace sem nome as esconde do resto do projeto)
namespace {
    constexpr int   FRAMES = 6;             // PLACEHOLDER: número de frames do sprite Boss_Walk.png (ajuste quando criar a arte)

    // Hitbox relativo ao canto superior esquerdo do sprite do chefe (64x64)
    constexpr float HITBOX_OFFSET_X = 16.0f;
    constexpr float HITBOX_OFFSET_Y = 24.0f;
    constexpr float HITBOX_WIDTH    = 32.0f;
    constexpr float HITBOX_HEIGHT   = 36.0f;

    constexpr float SPEED = 40.0f;          // Mais lento que o inimigo comum, mas mais perigoso
    constexpr int   MAX_HEALTH = 150;       // 15 tiros do cajado
    constexpr int   CONTACT_DAMAGE = 20;    // Dano ao encostar

    // O ataque: uma rajada de projéteis em anel (todas as direções ao mesmo tempo)
    constexpr float ATTACK_COOLDOWN = 1.5f;     // Segundos entre uma rajada e outra
    constexpr int   PROJECTILES_PER_BURST = 8;  // Quantos projéteis em cada rajada
    constexpr float PROJECTILE_SPEED = 140.0f;  // Velocidade de cada projétil
    constexpr int   PROJECTILE_DAMAGE = 15;     // Dano de cada projétil
    constexpr float PROJECTILE_LIFETIME = 3.0f; // Segundos até o projétil sumir
    constexpr float PROJECTILE_RADIUS = 6.0f;   // Raio de cada projétil
}

// Construtor: a BASE (Enemy) vem primeiro, e o chefe informa os valores dele (hitbox, vida, dano, velocidade)
MiniBoss::MiniBoss(float x, float y, const Texture2D &texture) :
    Enemy(x, y, texture, FRAMES, HITBOX_OFFSET_X, HITBOX_OFFSET_Y, HITBOX_WIDTH, HITBOX_HEIGHT, SPEED, MAX_HEALTH, CONTACT_DAMAGE),
    _attackCooldown(ATTACK_COOLDOWN),
    _attackTimer(ATTACK_COOLDOWN), // Começa em cooldown, para não atacar no instante em que o jogador entra na sala
    _projectilesPerBurst(PROJECTILES_PER_BURST),
    _projectileSpeed(PROJECTILE_SPEED),
    _projectileDamage(PROJECTILE_DAMAGE),
    _projectileLifetime(PROJECTILE_LIFETIME)
{
    // Nada a fazer aqui: tudo já foi inicializado na lista acima
}

// O chefe persegue como um inimigo comum e, além disso, conta o tempo para o próximo ataque
void MiniBoss::update(float dt, const std::vector<Rectangle> &walls)
{
    Enemy::update(dt, walls); // Reaproveita a perseguição, a animação e a invulnerabilidade da classe base

    if (_attackTimer > 0.0f) // Se ainda está em cooldown
    {
        _attackTimer -= dt; // Desconta o tempo
    }
}

// Rajada radial: quando o cooldown zera, dispara um anel de projéteis em volta do chefe
void MiniBoss::attack(std::vector<Projectile> &projectiles)
{
    if (_attackTimer > 0.0f)
    {
        return; // Ainda em cooldown, não ataca
    }

    Vector2 origin = getCenter(); // Os projéteis saem do centro do chefe
    float startAngle = (float)GetTime(); // O anel começa girado de forma diferente a cada rajada (o tempo muda sempre)

    for (int i = 0; i < _projectilesPerBurst; ++i)
    {
        // Divide a volta completa (2 * PI radianos) em partes iguais, uma para cada projétil
        float angle = startAngle + i * (2.0f * PI / _projectilesPerBurst);
        Vector2 direction = { cosf(angle), sinf(angle) }; // Direção de comprimento 1 apontando para esse ângulo

        // Projétil roxo, para ser diferente da bola de fogo laranja do jogador
        projectiles.emplace_back(origin, direction, _projectileSpeed, _projectileDamage,
                                 _projectileLifetime, PROJECTILE_RADIUS, Color{ 190, 80, 255, 255 });
    }

    _attackTimer = _attackCooldown; // Reinicia o cooldown
}
