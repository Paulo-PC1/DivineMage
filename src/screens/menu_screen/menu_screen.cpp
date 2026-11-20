// DivineMage - Shooter/src/screens/menu_screen/menu_screen.cpp
#include "screens/menu_screen/menu_screen.hpp" // Inclui o cabeçalho da classe MenuScreen
#include "core/config/config.hpp" // Inclui as constantes do jogo (tamanho da tela)

// Constantes e funções auxiliares que só este arquivo usa (o namespace sem nome as esconde do resto do projeto)
namespace {

    constexpr float BUTTON_WIDTH = 320.0f;
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

// Construtor: calcula a posição dos 3 botões, centralizados na tela, um embaixo do outro
MenuScreen::MenuScreen() :
    _playButton{    (Config::SCREEN_WIDTH - BUTTON_WIDTH) / 2.0f, 320.0f, BUTTON_WIDTH, BUTTON_HEIGHT },
    _creditsButton{ (Config::SCREEN_WIDTH - BUTTON_WIDTH) / 2.0f, 320.0f + (BUTTON_HEIGHT + BUTTON_SPACING), BUTTON_WIDTH, BUTTON_HEIGHT },
    _exitButton{    (Config::SCREEN_WIDTH - BUTTON_WIDTH) / 2.0f, 320.0f + 2.0f * (BUTTON_HEIGHT + BUTTON_SPACING), BUTTON_WIDTH, BUTTON_HEIGHT }
{
    // Nada a fazer aqui: tudo já foi inicializado na lista acima
}

// Devolve para onde o jogo deve ir (NONE = continuar no menu)
ScreenType MenuScreen::update(float)
{
    if (IsKeyPressed(KEY_ENTER)) // Atalho: ENTER também inicia o jogo
    {
        return ScreenType::GAMEPLAY;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) // Só reage ao momento do clique (e não ao botão segurado)
    {
        Vector2 mouse = GetMousePosition();

        if (CheckCollisionPointRec(mouse, _playButton))
        {
            return ScreenType::GAMEPLAY;
        }
        if (CheckCollisionPointRec(mouse, _creditsButton))
        {
            return ScreenType::CREDITS;
        }
        if (CheckCollisionPointRec(mouse, _exitButton))
        {
            return ScreenType::EXIT;
        }
    }

    return ScreenType::NONE;
}

// Desenha o menu
void MenuScreen::draw()
{
    ClearBackground(Color{ 20, 10, 35, 255 }); // Fundo roxo bem escuro

    // Título centralizado
    const char *title = "DIVINE MAGE";
    int titleSize = 80;
    DrawText(title, (Config::SCREEN_WIDTH - MeasureText(title, titleSize)) / 2, 130, titleSize, Color{ 255, 170, 50, 255 });

    const char *subtitle = "Um jogo de tiro e magia";
    int subtitleSize = 24;
    DrawText(subtitle, (Config::SCREEN_WIDTH - MeasureText(subtitle, subtitleSize)) / 2, 225, subtitleSize, Color{ 200, 180, 255, 255 });

    drawButton(_playButton, "JOGAR");
    drawButton(_creditsButton, "CREDITOS");
    drawButton(_exitButton, "SAIR");

    // Dica de controles no rodapé
    const char *hint = "WASD: mover   |   Mouse: mirar e atirar";
    int hintSize = 20;
    DrawText(hint, (Config::SCREEN_WIDTH - MeasureText(hint, hintSize)) / 2, Config::SCREEN_HEIGHT - 50, hintSize, GRAY);
}
