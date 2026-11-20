// DivineMage - Shooter/src/screens/game_screen/game_screen.cpp
#include "game_screen.hpp" // Inclui a classe GameScreen para gerenciar a tela de gameplay do jogo
#include "core/config/config.hpp" // Inclui a classe Config para acessar as configurações do jogo
#include "raylib.h" // Inclui a biblioteca Raylib para manipulação de gráficos e entrada do usuário

// Construtor da classe GameScreen, responsável por inicializar o jogador, a câmera e o mundo do jogo.
// O _world e o _hud usam o construtor padrão, por isso não aparecem na lista
GameScreen::GameScreen() : _player(0.0f, 0.0f, 85.0f), // A posição de verdade vem da sala (logo abaixo, no corpo do construtor)
    _camera(_player.getCenter(), { Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2 }, 0.0f, Config::CAMERA_ZOOM)
{
    // Carrega as 3 salas (mapas, inimigos, portas e loot)
    if (!_world.load())
    {
        TraceLog(LOG_ERROR, "GameScreen: nao carregou o mundo");
    }

    // Coloca o jogador no ponto de partida da sala inicial
    Vector2 spawn = _world.getCurrentRoom().getPlayerSpawn();
    _player.setPosition(spawn.x, spawn.y);

    // Informa à câmera o tamanho da sala e já a posiciona no jogador (evita um "pulo" no primeiro frame)
    _camera.setBounds((float)_world.getCurrentRoom().getPixelWidth(), (float)_world.getCurrentRoom().getPixelHeight());
    _camera.follow(_player.getCenter());
}
    
// Destrutor da classe GameScreen, responsável por liberar recursos alocados para o jogador, o mundo e o HUD.
GameScreen::~GameScreen() 
{
    _player.unload(); // Descarrega a textura do jogador
    _hud.unload(); // Descarrega a textura do HUD
    _world.unload(); // Descarrega as texturas de todas as salas
}

ScreenType GameScreen::update(float dt) 
{
    if (IsKeyPressed(KEY_ESCAPE)) // Atalho: ESC volta ao menu (o Game desliga o ESC como tecla de fechar a janela)
    {
        return ScreenType::MAIN_MENU;
    }

    Room &room = _world.getCurrentRoom(); // A sala em que o jogador está agora

    _player.update(dt, room.getCollisionRects()); // Atualiza o jogador (movimento e colisão com paredes e portas trancadas)

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) // Botão esquerdo apertado: atira
    {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), _camera.get()); // Converte a posição do mouse (tela) para a posição no mundo
        _player.shoot(mouseWorldPos, room.getPlayerProjectiles()); // Atira na direção do mouse (o tiro entra na lista de projéteis da sala)
    }

    _world.update(dt, _player); // Atualiza a sala: inimigos, projéteis, loot e troca de sala nas portas

    // A sala pode ter mudado no update acima, então pega a sala atual de novo
    Room &currentRoom = _world.getCurrentRoom();
    _camera.setBounds((float)currentRoom.getPixelWidth(), (float)currentRoom.getPixelHeight());
    _camera.follow(_player.getCenter()); // Atualiza a posição da câmera para seguir o jogador.

    if (_player.isDead())
    {
        return ScreenType::GAME_OVER; // Vida zerada: tela de game over
    }

    if (_world.isBossDefeated())
    {
        return ScreenType::CREDITS; // Chefe derrotado: fim do jogo, vai para os créditos
    }

    return ScreenType::NONE; // Retorna NONE para indicar que não há mudança de tela.
}

void GameScreen::draw() 
{
    ClearBackground(BLACK); // Fundo preto (aparece só se a câmera mostrar algo fora da sala)

    BeginMode2D(_camera.get()); // Inicia o modo 2D com a câmera definida.
        _world.draw(); // Primeiro a sala (mapa, portas, loot, inimigos e projéteis), para o jogador aparecer por cima
        _player.draw(); // Desenha o jogador na tela.
    EndMode2D(); // Encerra o modo 2D com a câmera definida.

    _hud.draw(_player); // O HUD é desenhado FORA do modo 2D, para ficar fixo na tela e sem o zoom da câmera
}
