// DivineMAge - Shooter/src/core/game/game.cpp
#include "game.hpp" // Inclui a classe Game para gerenciar o estado do jogo
#include "raylib.h" // Inclui a biblioteca Raylib para manipulação de gráficos e entrada do usuário
#include "core/config/config.hpp" // Inclui a classe Config para acessar as configurações do jogo
#include "screens/screen/screen.hpp" // Inclui a classe Screen para gerenciar a tela do jogo
#include "screens/game_screen/game_screen.hpp" // Inclui a classe GameScreen para gerenciar a tela de gameplay do jogo
#include <algorithm> // Inclui a biblioteca algorithm para utilizar a função std::min

Game::Game() : _currentScreen(nullptr), _shouldClose(false) // Inicializa ponteiro e variavel de controle da tela atual do jogo e da janela do jogo
{
    InitWindow(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, Config::WINDOW_TITLE); // Inicializa a janela do jogo com largura 1280, altura 720 e título "DivineMage"
    SetTargetFPS(Config::TARGET_FPS); // Define a taxa de quadros por segundo (FPS) para 60, garantindo uma atualização suave da tela e dos elementos do jogo.
    changeScreen(ScreenType::GAMEPLAY); // Define a tela inicial do jogo como a tela de gameplay, permitindo que o jogador comece a jogar imediatamente.
}

Game::~Game() // Destrutor da classe Game, responsável por fechar a janela do jogo e liberar recursos alocados.
{
    delete _currentScreen; // Libera a memória alocada para a tela atual do jogo, evitando vazamentos de memória.
    CloseWindow(); // Fecha a janela do jogo e libera os recursos alocados.
}

void Game::run() // Método para iniciar loop do jogo
{
    while(!WindowShouldClose() && !_shouldClose) // Loop principal do jogo, enquanto a janela não deve ser fechada e a variável de controle da janela do jogo não for verdadeira
    {
        float dt = std::min(GetFrameTime(), Config::MAX_DT); // Calcula o tempo de atualização do frame (delta time), garantindo uma atualização suave da tela e dos elementos do jogo.

        update(dt); // Atualiza o estado do jogo, incluindo a lógica de movimentação, colisões e outros elementos.
        draw(); // Desenha os elementos do jogo na tela, incluindo o jogador, inimigos, cenário e HUD.
    }
}

void Game::update(float dt) // Atualiza estado do jogo
{
    if (_currentScreen)
    {
        ScreenType nextScreen = _currentScreen->update(dt); // Atualiza a tela atual do jogo, incluindo a lógica de movimentação, colisões e outros elementos.
        if (nextScreen != ScreenType::NONE) // Se a tela atual do jogo retornar um tipo de tela diferente de NONE
        {
            changeScreen(nextScreen); // Muda para a próxima tela do jogo, permitindo transições entre diferentes estados do jogo (ex: menu, gameplay, pause).
        }
    }
}

void Game::draw() // Desenha elementos do jogo na tela
{
    BeginDrawing(); // Inicia o desenho na tela
    ClearBackground(RAYWHITE); // Limpa a tela com a cor selecionada

    if (_currentScreen)
    {
        _currentScreen->draw(); // Desenha a tela atual do jogo, incluindo o jogador, inimigos, cenário e HUD.
    }

    EndDrawing(); // Encerra o desenho na tela e troca os buffers (double buffering)
}

void Game::changeScreen(ScreenType screenType) // Muda tela atual do jogo
{
    Screen* newScreen = nullptr; // Inicializa ponteiro para a nova tela do jogo como nulo
    
    switch(screenType) // Verifica o tipo de tela a ser exibida
    {
        case ScreenType::MAIN_MENU:
            // newScreen = new MenuScreen(); // Cria uma nova instância da tela do menu principal do jogo
            break;
        case ScreenType::GAMEPLAY:
            newScreen = new GameScreen(); // Cria uma nova instância da tela de gameplay do jogo
            break;
        case ScreenType::CREDITS:
            // newScreen = new CreditsScreen(); // Cria uma nova instância da tela de créditos do jogo
            break;
        case ScreenType::GAME_OVER:
            // newScreen = new GameOverScreen(); // Cria uma nova instância da tela de game over do jogo
            break;
        case ScreenType::EXIT:
            _shouldClose = true; // Define a variável de controle da janela do jogo como verdadeira, indicando que a janela deve ser fechada
            break;
        default:
            break;
    }
    
    if(newScreen != nullptr) // Se a nova tela do jogo não for nula
    {
        delete _currentScreen; // Libera a memória alocada para a tela atual do jogo, evitando vazamentos de memória.
        _currentScreen = newScreen; // Define a nova tela do jogo como a tela atual do jogo
    }
}