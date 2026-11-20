// DivineMage - Shooter/src/weapons/projectile/projectile.cpp
#include "weapons/projectile/projectile.hpp" // Inclusão do cabeçalho da classe
#include "raymath.h" // Inclui a biblioteca Raymath para operações matemáticas, como normalização de vetores
#include <cmath> // sinf e cosf (usados nos efeitos da bola de fogo)

// Funções auxiliares que só este arquivo usa (o namespace sem nome as esconde do resto do projeto)
namespace {

    // Mistura duas cores: t = 0 devolve a cor "a", t = 1 devolve a cor "b", valores no meio dão cores intermediárias
    Color mixColor(Color a, Color b, float t)
    {
        return Color{
            (unsigned char)(a.r + (b.r - a.r) * t), // Mistura o canal vermelho
            (unsigned char)(a.g + (b.g - a.g) * t), // Mistura o canal verde
            (unsigned char)(a.b + (b.b - a.b) * t), // Mistura o canal azul
            255                                     // Totalmente opaca (a transparência é aplicada depois com Fade)
        };
    }
}

Projectile::Projectile(Vector2 center, Vector2 direction, float speed, int damage, float lifetime, float radius, Color color)
    : Entity(center.x - radius, center.y - radius, 0, 0, radius * 2, radius * 2), // Converte o centro recebido no canto superior esquerdo do hitbox
    _direction(Vector2Normalize(direction)), // Normaliza a direção (comprimento 1)
    _speed(speed),
    _damage(damage),
    _lifetimeLeft(lifetime),
    _radius(radius),
    _color(color),
    _alive(true) 
{
    
}

void Projectile::update(float dt, const std::vector<Rectangle> &walls) {
    if (!_alive) return; // Projétil morto não se atualiza

    // Atualiza a posição do projétil
    _x += _direction.x * _speed * dt;
    _y += _direction.y * _speed * dt;

    // Atualiza o tempo de vida restante
    _lifetimeLeft -= dt;
    if (_lifetimeLeft <= 0) {
        _alive = false; // O projétil morre quando o tempo de vida acaba
        return;
    }

    // Verifica colisão com paredes
    Rectangle hitbox = getHitbox(); // Pega o hitbox uma vez, na posição já atualizada
    for (const Rectangle &wall : walls) {
        if (CheckCollisionRecs(hitbox, wall)) {
            _alive = false; // O projétil morre ao colidir com uma parede
            return;
        }
    }
}

// Desenha uma bola de fogo. Tudo é feito com círculos sobrepostos, em 4 camadas (de trás para frente)
void Projectile::draw() const {
    if(!_alive)
    {
        return; // Projétil morto não é desenhado
    }

    Vector2 center = getCenter(); // O desenho é centrado no hitbox, que é onde a colisão acontece

    // Tremular: o tamanho oscila um pouco com o passar do tempo (usa o tempo de vida restante, que diminui sozinho)
    float flicker = 1.0f + 0.15f * sinf(_lifetimeLeft * 40.0f);

    // Camada 1: a cauda de fogo. Círculos atrás da bola (direção contrária ao movimento), cada vez menores e mais transparentes
    Color tailColor = mixColor(_color, RED, 0.6f); // A cauda é mais avermelhada que a bola
    for (int i = 5; i >= 1; --i) // De trás para frente, para os círculos próximos ficarem por cima
    {
        float distance = _radius * 0.9f * i; // Quanto mais longe da bola, maior o i
        Vector2 tailPos = { center.x - _direction.x * distance, center.y - _direction.y * distance };
        float tailRadius = _radius * (1.0f - 0.15f * i); // Fica menor com a distância
        float tailAlpha = 0.55f - 0.09f * i;             // Fica mais transparente com a distância
        DrawCircleV(tailPos, tailRadius, Fade(tailColor, tailAlpha));
    }

    // Camada 2: o brilho. O modo aditivo SOMA as cores com o fundo, o que cria o efeito de luz
    BeginBlendMode(BLEND_ADDITIVE);
        DrawCircleV(center, _radius * 2.4f * flicker, Fade(_color, 0.18f)); // Halo externo (bem fraco)
        DrawCircleV(center, _radius * 1.7f * flicker, Fade(_color, 0.30f)); // Halo interno
    EndBlendMode();

    // Camada 3: o corpo da bola, em três círculos, cada um mais claro e menor que o anterior
    DrawCircleV(center, _radius * 1.15f * flicker, _color);                           // Chama externa (cor base)
    DrawCircleV(center, _radius * 0.80f * flicker, mixColor(_color, YELLOW, 0.75f));  // Chama do meio (amarelada)
    DrawCircleV(center, _radius * 0.40f, mixColor(_color, WHITE, 0.90f));             // Núcleo quase branco

    // Camada 4: duas faíscas girando em volta da bola
    float t = _lifetimeLeft; // Qualquer valor que mude com o tempo serve para movimentar as faíscas
    Vector2 spark1 = { center.x + cosf(t * 17.0f) * _radius * 1.8f,        center.y + sinf(t * 17.0f) * _radius * 1.8f };
    Vector2 spark2 = { center.x + cosf(t * 23.0f + 2.0f) * _radius * 2.2f, center.y + sinf(t * 23.0f + 2.0f) * _radius * 2.2f };
    DrawCircleV(spark1, 1.0f, YELLOW);
    DrawCircleV(spark2, 1.0f, mixColor(_color, YELLOW, 0.5f));
}

bool Projectile::isAlive() const {
    return _alive;
}

void Projectile::destroy(){
    _alive = false;
}

int Projectile::getDamage() const {
    return _damage;
}
