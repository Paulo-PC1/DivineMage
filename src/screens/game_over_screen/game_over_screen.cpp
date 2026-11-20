// DivineMage - Shooter/src/screens/game_over_screen/game_over_screen.cpp
#include "screens/game_over_screen/game_over_screen.hpp" // Inclui o cabeçalho da classe GameOverScreen
#include "core/config/config.hpp" // Inclui as constantes do jogo (tamanho da tela)

// Constantes e funções auxiliares que só este arquivo usa (o namespace sem nome as esconde do resto do projeto)
namespace {

    constexpr float BUTTON_WIDTH = 360.0f;
    constexpr float BUTTON_HEIGHT = 64.0f;
    constexpr float BUTTON_SPACING = 24.0f; // Espaço vertical entre os botões

    // Desenha um botão: o fundo clareia quando o mouse está em cima
    void drawButton(const Rectangle &rect, const char *label)
    {
        bool hover = CheckCollisionPointRec(GetMousePosition(), rect); // O mouse está em cima do botão?

        DrawRectangleRec(rect, hover ? Color{ 120, 60, 200, 255 } : Color{ 60, 30, 110, 255 });
        DrawRectangleLinesEx(rect, 3.0f, hover ? WHITE : Color{ 180, 150, 255, 255 });

        int fontSize = 28;
        int textWidth = MeasureText(label, fontSize); // Largura do texto, para centralizar
        DrawText(label, (int)(rect.x + (rect.width - textWidth) / 2.0f), (int)(rect.y + (rect.height - fontSize) / 2.0f), fontSize, WHITE);
    }
}

// Construtor: calcula a posição dos 2 botões, centralizados na tela
GameOverScreen::GameOverScreen() :
    _retryButton{ (Config::SCREEN_WIDTH - BUTTON_WIDTH) / 2.0f, 340.0f, BUTTON_WIDTH, BUTTON_HEIGHT },
    _menuButton{  (Config::SCREEN_WIDTH - BUTTON_WIDTH) / 2.0f, 340.0f + (BUTTON_HEIGHT + BUTTON_SPACING), BUTTON_WIDTH, BUTTON_HEIGHT }

{
    // Nada a fazer aqui: tudo já foi inicializado na lista acima
    _music.load(ASSETS_PATH "audio/music/game_over.mp3");
    _music.setVolume(0.5f);
    _music.play();
}

// Devolve para onde o jogo deve ir (NONE = continuar nesta tela)
ScreenType GameOverScreen::update(float)
{
    _music.update();
    if (IsKeyPressed(KEY_ENTER)) // Atalho: ENTER tenta de novo
    {
        return ScreenType::GAMEPLAY;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector2 mouse = GetMousePosition();

        if (CheckCollisionPointRec(mouse, _retryButton))
        {
            return ScreenType::GAMEPLAY; // O Game cria uma GameScreen nova, então o jogo recomeça do zero
        }
        if (CheckCollisionPointRec(mouse, _menuButton))
        {
            return ScreenType::MAIN_MENU;
        }
    }

    return ScreenType::NONE;
}

// Desenha a tela de game over
void GameOverScreen::draw()
{
    ClearBackground(Color{ 25, 5, 10, 255 }); // Fundo vermelho bem escuro

    const char *title = "GAME OVER";
    int titleSize = 96;
    DrawText(title, (Config::SCREEN_WIDTH - MeasureText(title, titleSize)) / 2, 140, titleSize, Color{ 220, 40, 50, 255 });

    const char *subtitle = "Voce foi derrotado...";
    int subtitleSize = 28;
    DrawText(subtitle, (Config::SCREEN_WIDTH - MeasureText(subtitle, subtitleSize)) / 2, 260, subtitleSize, LIGHTGRAY);

    drawButton(_retryButton, "TENTAR DE NOVO");
    drawButton(_menuButton, "MENU PRINCIPAL");
}
