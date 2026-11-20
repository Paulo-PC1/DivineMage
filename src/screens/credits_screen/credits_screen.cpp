// DivineMage - Shooter/src/screens/credits_screen/credits_screen.cpp
#include "screens/credits_screen/credits_screen.hpp" // Inclui o cabeçalho da classe CreditsScreen
#include "core/config/config.hpp" // Inclui as constantes do jogo (tamanho da tela)

// Constantes e funções auxiliares que só este arquivo usa (o namespace sem nome as esconde do resto do projeto)
namespace {

    constexpr float BUTTON_WIDTH = 280.0f;
    constexpr float BUTTON_HEIGHT = 56.0f;

    // Linhas dos créditos. PLACEHOLDER: troque os textos entre colchetes pelos nomes reais
    // (sem acentos de propósito: a fonte padrão do raylib pode não desenhar todos os acentos)
    constexpr const char *LINES[] = {
        "Programacao e Design: Paulo Cezar",
        "Arte (sprites e tilesets): Natalia Daiane e Paulo Cezar",
        "Disciplina: Programacao Orientada a Objetos",
        "Professor: [Paulo Giovani]",
        "Musicas: 16-Bit Fantasy & Adventure Music Pack - by xDeviruchi ",
        "Feito com C++ e raylib",
    };
    constexpr int LINE_COUNT = sizeof(LINES) / sizeof(LINES[0]); // Quantas linhas existem no array

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

// Construtor: posiciona o botão Voltar, centralizado perto do rodapé
CreditsScreen::CreditsScreen() :
    _backButton{ (Config::SCREEN_WIDTH - BUTTON_WIDTH) / 2.0f, Config::SCREEN_HEIGHT - 120.0f, BUTTON_WIDTH, BUTTON_HEIGHT }

{
    // Nada a fazer aqui: tudo já foi inicializado na lista acima
    _music.load(ASSETS_PATH "audio/music/credits.mp3");
    _music.setVolume(0.5f);
    _music.play();
}

// Volta ao menu com o botão, ESC ou ENTER
ScreenType CreditsScreen::update(float)
{
    _music.update();
    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER)) // O ESC só funciona porque o Game desliga a tecla de fechar a janela
    {
        return ScreenType::MAIN_MENU;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), _backButton))
    {
        return ScreenType::MAIN_MENU;
    }

    return ScreenType::NONE;
}

// Desenha os créditos
void CreditsScreen::draw()
{
    ClearBackground(Color{ 20, 10, 35, 255 });

    const char *title = "CREDITOS";
    int titleSize = 72;
    DrawText(title, (Config::SCREEN_WIDTH - MeasureText(title, titleSize)) / 2, 80, titleSize, Color{ 255, 170, 50, 255 });

    int lineSize = 28;
    int y = 220; // Posição vertical da primeira linha
    for (int i = 0; i < LINE_COUNT; ++i)
    {
        DrawText(LINES[i], (Config::SCREEN_WIDTH - MeasureText(LINES[i], lineSize)) / 2, y, lineSize, WHITE);
        y += 44; // Desce para a próxima linha
    }

    drawButton(_backButton, "VOLTAR");
}
