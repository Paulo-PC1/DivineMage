// DivineMage - Shooter/src/screens/game_screen/game_screen.cpp
#include "game_screen.hpp" // Inclui a classe GameScreen para gerenciar a tela de gameplay do jogo
#include "core/config/config.hpp" // Inclui a classe Config para acessar as configurações do jogo
#include "raylib.h" // Inclui a biblioteca Raylib para manipulação de gráficos e entrada do usuário

// Construtor da classe GameScreen, responsável por inicializar o jogador e a câmera do jogo.
GameScreen::GameScreen() : _player(320.0f, 192.0f, 85.0f),
    _camera(_player.getCenter(), { Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2 }, 0.0f, Config::CAMERA_ZOOM)
{
    if (!_tilemap.load(ASSETS_PATH "maps/room1.json", ASSETS_PATH "tilesets/dungeon_tiles.png"))
    {
        TraceLog(LOG_ERROR, "GameScreen: nao carregou a sala 1");
    }

    // Informa à câmera o tamanho da sala (640 x 384 px)
    _camera.setBounds((float)_tilemap.getPixelWidth(), (float)_tilemap.getPixelHeight());
}
    
// Destrutor da classe GameScreen, responsável por liberar recursos alocados para o jogador e a câmera do jogo.
GameScreen::~GameScreen() 
{
    
    _player.unload(); // Descarrega a textura do jogador
}

ScreenType GameScreen::update(float dt) 
{
    
    _player.update(dt, _tilemap.getWallRects()); // Atualiza o estado do jogador, incluindo a lógica de movimentação, colisões e outros elementos.
    _camera.follow(_player.getCenter()); // Atualiza a posição da câmera para seguir o jogador.

    return ScreenType::NONE; // Retorna NONE para indicar que não há mudança de tela.
}

void GameScreen::draw() 
{
    
    BeginMode2D(_camera.get()); // Inicia o modo 2D com a câmera definida.
        _tilemap.draw(); // Primeiro o mapa, para o jogador aparecer por cima
        _player.draw(); // Desenha o jogador na tela.
    EndMode2D(); // Encerra o modo 2D com a câmera definida.

    DrawText("Vida: 100", 10, 10, 20, BLACK); // Desenha o texto de HUD na tela (Exemplo de HUD).
}