//DivineMage - Shooter/src/core/camera/camera.cpp
#include "camera.hpp" // Inclui a Classe camera 
#include "raymath.h" // Inclui a biblioteca Raymath.h para uso de Clamp

// Função que inicializa a camera
GameCamera::GameCamera(Vector2 target, Vector2 offset, float rotation, float zoom) :
    _worldWidth(0.0f), _worldHeight(0.0f) // Sem limites até alguém chamar setBounds
{
    
    _camera = { 0 }; // Inicializa a camera com o valor padrao 0
    _camera.target = target; // Define o ponto do mundo que a camera aponta
    _camera.offset = offset; // define onde o ponto do mundo que a camera aponta vai ser renderizado na tela
    _camera.rotation = rotation; // define a rocatção da camera
    _camera.zoom = zoom; // define o zoom da camera 
}
// Guarda o tamanho do mundo (da sala atual) em pixels
void GameCamera::setBounds(float worldWidth, float worldHeight)
{
    _worldWidth = worldWidth;
    _worldHeight = worldHeight;
}

// função que atualiza a posição da camera para seguir o jogador, sem sair dos limites da sala
void GameCamera::follow(Vector2 target)
{
    // Meia visão: quanto do mundo a câmera enxerga de cada lado do alvo
    // (offset está em pixels de tela, e o zoom amplia o mundo, então divide-se pelo zoom)
    float halfViewX = _camera.offset.x / _camera.zoom;
    float halfViewY = _camera.offset.y / _camera.zoom;

    // Só limita se os limites foram definidos (maiores que zero)
    if (_worldWidth > 0.0f && _worldHeight > 0.0f)
    {
        // Eixo X
        if (_worldWidth > 2.0f * halfViewX)
        {
            target.x = Clamp(target.x, halfViewX, _worldWidth - halfViewX); // Sala maior que a visão: prende o alvo
        }
        else
        {
            target.x = _worldWidth / 2.0f; // Sala menor que a visão: centraliza na sala
        }

        // Eixo Y
        if (_worldHeight > 2.0f * halfViewY)
        {
            target.y = Clamp(target.y, halfViewY, _worldHeight - halfViewY);
        }
        else
        {
            target.y = _worldHeight / 2.0f;
        }
    }

    _camera.target = target; // atualiza o ponto do mundo que a camera aponta
}


// Getter que retorna a camera "crua" do raylib
Camera2D GameCamera::get() const
{
    return _camera; // retorna a camera "crua" do raylib
}