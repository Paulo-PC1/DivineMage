// DivineMage - Shooter/src/rooms/door/door.cpp
#include "rooms/door/door.hpp" // Inclui o cabeçalho da classe Door
#include <algorithm> // std::min

namespace {
    constexpr int OPEN_FRAME = 0; // No Door.png, o frame 0 é sempre a porta aberta
}

// Construtor: a porta nasce TRANCADA (a Room a destranca quando todos os inimigos morrem)
Door::Door(Rectangle area, int targetRoom, Vector2 spawnInTarget, int closedFrame) :
    _area(area),
    _targetRoom(targetRoom),
    _spawnInTarget(spawnInTarget),
    _locked(true),
    _closedFrame(closedFrame),
    _texture(nullptr) // A Room entrega a textura depois, com setTexture
{
    // Nada a fazer aqui: tudo já foi inicializado na lista acima
}

// Tranca a porta (ela volta a ser uma parede na colisão)
void Door::lock()
{
    _locked = true;
}

// Destranca a porta (ela passa a levar para a outra sala)
void Door::unlock()
{
    _locked = false;
}

bool Door::isLocked() const
{
    return _locked;
}

// Desenha a porta. O sprite Door.png tem 4 frames de 32x32 lado a lado:
// frame 0 = aberta, frame 1 = fechada vermelha, frame 2 = fechada azul, frame 3 = fechada roxa
void Door::draw() const
{
    if (_texture != nullptr && _texture->id != 0) // Se o sprite existe
    {
        // Quantos frames cabem na imagem (largura da imagem dividida pela largura de um frame)
        int frameCount = (int)(_texture->width / _area.width);

        // Trancada usa o frame fechado da sala; se a imagem tiver menos frames que isso
        // (ex: um Door.png antigo de 2 frames), usa o último frame que existe
        int closedFrame = std::max(0, std::min(_closedFrame, frameCount - 1)); // O max(0, ...) protege contra uma imagem menor que 1 frame
        int frame = _locked ? closedFrame : OPEN_FRAME;
        Rectangle sourceRec = { frame * _area.width, 0.0f, _area.width, _area.height }; // Recorte do frame dentro da folha
        DrawTextureRec(*_texture, sourceRec, Vector2{ _area.x, _area.y }, WHITE);
        return;
    }

    // PLACEHOLDER: sem sprite (Door.png ainda não existe), desenha formas simples
    if (_locked)
    {
        DrawRectangleRec(_area, Color{ 70, 20, 20, 255 }); // Porta fechada: vermelho escuro
        DrawRectangleLinesEx(_area, 2.0f, RED);
        for (int i = 1; i < 4; ++i) // Três grades verticais, para parecer trancada
        {
            int barX = (int)(_area.x + i * (_area.width / 4.0f));
            DrawLine(barX, (int)_area.y, barX, (int)(_area.y + _area.height), RED);
        }
    }
    else
    {
        DrawRectangleRec(_area, Fade(SKYBLUE, 0.35f)); // Porta aberta: azul claro translúcido (parece um portal)
        DrawRectangleLinesEx(_area, 2.0f, SKYBLUE);
    }
}

// A porta leva para outra sala se estiver destrancada e o hitbox estiver encostando nela
bool Door::isTouching(const Rectangle &hitbox) const
{
    return !_locked && CheckCollisionRecs(_area, hitbox);
}

// Área da porta (trancada, a Room a usa como parede)
Rectangle Door::getArea() const
{
    return _area;
}

// Índice da sala para onde a porta leva
int Door::getTargetRoom() const
{
    return _targetRoom;
}

// Onde o jogador aparece na sala de destino
Vector2 Door::getSpawnInTarget() const
{
    return _spawnInTarget;
}

// Guarda o endereço da textura (a Room é a dona dela)
void Door::setTexture(const Texture2D *texture)
{
    _texture = texture;
}
