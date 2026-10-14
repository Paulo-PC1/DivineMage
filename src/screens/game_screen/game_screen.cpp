// DivineMage - Shooter/src/screens/game_screen/game_screen.cpp
#include "game_screen.hpp" // Inclui a classe GameScreen para gerenciar a tela de gameplay do jogo
#include "core/config/config.hpp" // Inclui a classe Config para acessar as configurações do jogo
#include "raylib.h" // Inclui a biblioteca Raylib para manipulação de gráficos e entrada do usuário

// Construtor da classe GameScreen, responsável por inicializar o jogador e a câmera do jogo.
GameScreen::GameScreen() : _player(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2, 60.0f),
    _camera(_player.getCenter(), { Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2 }, 0.0f, Config::CAMERA_ZOOM)
{
    
}

// Destrutor da classe GameScreen, responsável por liberar recursos alocados para o jogador e a câmera do jogo.
GameScreen::~GameScreen() {
    _player.unload(); // Descarrega a textura do jogador
}

ScreenType GameScreen::update(float dt) {
    _player.update(dt); // Atualiza o estado do jogador, incluindo a lógica de movimentação, colisões e outros elementos.
    _camera.follow(_player.getCenter()); // Atualiza a posição da câmera para seguir o jogador.

    return ScreenType::NONE; // Retorna NONE para indicar que não há mudança de tela.
}

void GameScreen::draw() {
    BeginMode2D(_camera.get()); // Inicia o modo 2D com a câmera definida.
        DrawText(Config::WINDOW_TITLE, Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2, 20, BLACK); // Desenha o título do jogo na tela.
        _player.draw(); // Desenha o jogador na tela.
    EndMode2D(); // Encerra o modo 2D com a câmera definida.

    DrawText("Vida: 100", 10, 10, 20, BLACK); // Desenha o texto de HUD na tela (Exemplo de HUD).
}