// DivineMage - Shooter/src/entities/pickup/pickup.cpp
#include "entities/pickup/pickup.hpp" // Inclui o cabeçalho da classe Pickup
#include "entities/actor/actor.hpp" // Definição completa de Actor (necessária para a poção usar o alvo)
#include <cmath> // sinf

// Constantes do item (o namespace sem nome as esconde do resto do projeto)
namespace {
    // O sprite da poção tem 32x32, e o hitbox é um pouco menor que ele (facilita pegar o item)
    constexpr float HITBOX_OFFSET = 4.0f;
    constexpr float HITBOX_SIZE   = 24.0f;
}

// Construtor: a BASE (Entity) vem primeiro. A poção usa o valor padrão de cura (30)
Pickup::Pickup(float x, float y) :
    Entity(x, y, HITBOX_OFFSET, HITBOX_OFFSET, HITBOX_SIZE, HITBOX_SIZE),
    _potion(), // Poção de vida com o valor padrão
    _collected(false),
    _texture(nullptr) // A Room entrega a textura depois, com setTexture
{
    // Nada a fazer aqui: tudo já foi inicializado na lista acima
}

// O item não se move nem tem lógica própria, mas o Entity obriga a existir um update (é virtual puro)
void Pickup::update(float, const std::vector<Rectangle> &)
{
    // Sem nome nos parâmetros, porque eles não são usados
}

// Desenha a poção flutuando levemente
void Pickup::draw() const
{
    if (_collected)
    {
        return; // Já foi coletada, não desenha
    }

    // Flutuar: sobe e desce 2 pixels, seguindo o tempo (só o desenho se move, o hitbox fica parado)
    float bob = sinf((float)GetTime() * 3.0f) * 2.0f;

    if (_texture != nullptr && _texture->id != 0) // Se o sprite existe
    {
        DrawTextureV(*_texture, Vector2{ _x, _y + bob }, WHITE);
        return;
    }

    // PLACEHOLDER: sem sprite (Health_Potion.png ainda não existe), desenha um frasco vermelho com formas simples
    Vector2 center = getCenter();
    center.y += bob;

    BeginBlendMode(BLEND_ADDITIVE);
        DrawCircleV(center, 14.0f, Fade(RED, 0.20f)); // Brilho em volta, para chamar atenção
    EndBlendMode();

    DrawCircleV(center, 8.0f, RED); // Corpo do frasco
    DrawCircleV(Vector2{ center.x - 3.0f, center.y - 3.0f }, 2.0f, Fade(WHITE, 0.8f)); // Reflexo de luz
    DrawRectangle((int)center.x - 3, (int)center.y - 14, 6, 7, LIGHTGRAY); // Gargalo
    DrawRectangle((int)center.x - 4, (int)center.y - 16, 8, 3, BROWN); // Rolha
}

// Tenta coletar o item. A poção decide se pode ser usada (a de vida não pode, se a vida estiver cheia)
bool Pickup::tryCollect(Actor &target)
{
    if (_collected)
    {
        return false; // Já foi coletada
    }

    if (!_potion.canApply(target)) // Ex: vida cheia
    {
        return false; // Não foi usada, então o item continua no lugar
    }

    _potion.apply(target); // Usa a poção automaticamente
    _collected = true; // Marca como coletada (a Room remove o item depois)
    return true;
}

bool Pickup::isCollected() const
{
    return _collected;
}

// Guarda o endereço da textura (a Room é a dona dela)
void Pickup::setTexture(const Texture2D *texture)
{
    _texture = texture;
}
