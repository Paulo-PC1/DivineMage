// DivineMage - Shooter/src/entities/enemy/enemy.cpp
#include "entities/enemy/enemy.hpp" // Inclui o cabeçalho da classe Enemy
#include "raymath.h" // Inclui a biblioteca Raymath para operações com vetores (subtrair, normalizar, escalar)
#include <cmath> // fabsf

// Constantes do inimigo comum (o namespace sem nome as esconde do resto do projeto)
namespace {
    constexpr int   FRAMES = 6;             // PLACEHOLDER: número de frames do sprite Enemy_Walk.png (ajuste quando criar a arte)
    constexpr float FRAME_TIME = 0.15f;     // Segundos que cada frame da animação fica na tela

    // Hitbox relativo ao canto superior esquerdo do sprite (32x32), no mesmo formato do jogador
    constexpr float HITBOX_OFFSET_X = 9.0f;
    constexpr float HITBOX_OFFSET_Y = 16.0f;
    constexpr float HITBOX_WIDTH    = 14.0f;
    constexpr float HITBOX_HEIGHT   = 16.0f;

    constexpr float SPEED = 55.0f;          // Velocidade do inimigo (o jogador tem 85, então dá para fugir)
    constexpr int   MAX_HEALTH = 30;        // Vida máxima: 3 tiros do cajado (10 de dano cada)
    constexpr int   CONTACT_DAMAGE = 10;    // Dano que causa ao encostar no jogador
    constexpr float STOP_DISTANCE = 2.0f;   // Perto assim do alvo o inimigo para (evita tremer em cima do jogador)
}

// Construtor público: usado para criar o inimigo comum
// Ele CHAMA o construtor protegido (logo abaixo), passando os valores padrão deste arquivo
Enemy::Enemy(float x, float y, const Texture2D &texture) :
    Enemy(x, y, texture, FRAMES, HITBOX_OFFSET_X, HITBOX_OFFSET_Y, HITBOX_WIDTH, HITBOX_HEIGHT, SPEED, MAX_HEALTH, CONTACT_DAMAGE)
{
    // Nada a fazer aqui: o outro construtor já fez tudo
}

// Construtor protegido: usado por este construtor público e também pelo MiniBoss (que informa valores próprios)
Enemy::Enemy(float x, float y, const Texture2D &texture, int totalFrames,
             float hitboxOffsetX, float hitboxOffsetY, float hitboxWidth, float hitboxHeight,
             float speed, int maxHealth, int contactDamage) :
    Actor(x, y, hitboxOffsetX, hitboxOffsetY, hitboxWidth, hitboxHeight, speed, maxHealth), // A BASE vem primeiro
    _target(getCenter()), // Começa mirando em si mesmo (a Room corrige isso todo frame com setTarget)
    _contactDamage(contactDamage),
    _texture(&texture), // Guarda o ENDEREÇO da textura (a Room é a dona dela, o inimigo só usa)
    _anim(texture, totalFrames, FRAME_TIME),
    _facingLeft(false)
{
    // Nada a fazer aqui: tudo já foi inicializado na lista acima
}

// Persegue o alvo: anda em linha reta na direção dele, respeitando as paredes
void Enemy::update(float dt, const std::vector<Rectangle> &walls)
{
    Vector2 toTarget = Vector2Subtract(_target, getCenter()); // Vetor que vai do inimigo até o alvo
    float distance = Vector2Length(toTarget); // Distância até o alvo

    if (distance > STOP_DISTANCE) // Só anda se ainda estiver longe do alvo
    {
        Vector2 direction = Vector2Normalize(toTarget); // Direção de comprimento 1 (mesma ideia do movimento do jogador)
        Vector2 displacement = Vector2Scale(direction, _speed * dt); // Quanto andar neste frame
        moveWithCollision(displacement, walls); // Método do Actor: move sem atravessar paredes

        if (fabsf(direction.x) > 0.1f) // Só vira de lado se o alvo estiver realmente para um dos lados
        {
            _facingLeft = (direction.x < 0.0f);
        }
    }

    _anim.update(dt); // Avança a animação de andar
    updateInvulnerability(dt); // Método do Actor (o inimigo comum tem duração 0, então não faz efeito)
}

// Desenha o inimigo: sprite se existir, senão um retângulo de placeholder
void Enemy::draw() const
{
    if (_texture == nullptr || _texture->id == 0) // Sem sprite (o PNG ainda não foi criado)
    {
        Rectangle hitbox = getHitbox();
        DrawRectangleRec(hitbox, MAROON); // Retângulo vermelho escuro no lugar do corpo
        DrawRectangleLinesEx(hitbox, 1.0f, RED); // Borda vermelha
    }
    else
    {
        Rectangle sourceRec = _anim.getFrameRec(); // Recorte do frame atual dentro da folha de sprites
        if (_facingLeft)
        {
            sourceRec.width = -sourceRec.width; // Espelha na hora do desenho, igual ao jogador
        }
        DrawTextureRec(*_texture, sourceRec, Vector2{ _x, _y }, WHITE); // Desenha o frame atual
    }

    // Barra de vida: só aparece depois que o inimigo leva dano
    if (_health < _maxHealth)
    {
        Rectangle hitbox = getHitbox();
        float ratio = (float)_health / (float)_maxHealth; // De 0 a 1
        DrawRectangle((int)hitbox.x, (int)hitbox.y - 6, (int)hitbox.width, 3, Fade(BLACK, 0.7f)); // Fundo da barra
        DrawRectangle((int)hitbox.x, (int)hitbox.y - 6, (int)(hitbox.width * ratio), 3, RED); // Parte cheia da barra
    }
}

// Ataque do inimigo comum: não faz nada (só causa dano ao encostar).
// O MiniBoss sobrescreve este método, e no futuro inimigos atiradores também
void Enemy::attack(std::vector<Projectile> &)
{
    // Sem nome no parâmetro, porque ele não é usado aqui
}

// A Room informa onde está o jogador (o update não recebe o jogador)
void Enemy::setTarget(Vector2 targetPosition)
{
    _target = targetPosition;
}

// Dano que o inimigo causa ao encostar no jogador (a Room aplica)
int Enemy::getContactDamage() const
{
    return _contactDamage;
}
