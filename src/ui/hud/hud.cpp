// DivineMage - Shooter/src/ui/hud/hud.cpp
#include "ui/hud/hud.hpp" // Inclui o cabeçalho da classe Hud
#include "entities/player/player.hpp" // Definição completa de Player (precisa de getHealth e getMaxHealth)

// Constantes que só este arquivo usa (o namespace sem nome as esconde do resto do projeto)
namespace {

    // PLACEHOLDER: exporte o heart.aseprite para PNG com este nome (um coração só, quadrado).
    // Enquanto o arquivo não existir, o jogo desenha um coração com formas simples
    constexpr const char *HEART_SPRITE = ASSETS_PATH "sprites/hud/heart.png";

    constexpr float MARGIN = 16.0f;      // Distância da borda da tela
    constexpr float ICON_SIZE = 32.0f;   // Tamanho do ícone do coração, em pixels
    constexpr float BAR_WIDTH = 220.0f;  // Largura da barra de vida
    constexpr float BAR_HEIGHT = 20.0f;  // Altura da barra de vida

    // Desenha um coração com formas simples (dois círculos em cima e um triângulo embaixo)
    void drawHeartShape(Vector2 center, float size, Color color)
    {
        float radius = size * 0.28f;
        DrawCircleV(Vector2{ center.x - size * 0.22f, center.y - size * 0.12f }, radius, color); // Lobo esquerdo
        DrawCircleV(Vector2{ center.x + size * 0.22f, center.y - size * 0.12f }, radius, color); // Lobo direito

        // Ponta de baixo (os vértices precisam estar em sentido anti-horário: esquerda, baixo, direita)
        DrawTriangle(
            Vector2{ center.x - size * 0.48f, center.y - size * 0.02f },
            Vector2{ center.x,                center.y + size * 0.48f },
            Vector2{ center.x + size * 0.48f, center.y - size * 0.02f },
            color);
    }
}

// Construtor: carrega o ícone se o arquivo existir
Hud::Hud() :
    _heartTexture{} // Começa vazia (id = 0)
{
    if (FileExists(HEART_SPRITE))
    {
        _heartTexture = LoadTexture(HEART_SPRITE);
        SetTextureFilter(_heartTexture, TEXTURE_FILTER_POINT); // Pixels nítidos
    }
}

// Descarrega a textura, se houver
void Hud::unload()
{
    if (_heartTexture.id != 0)
    {
        UnloadTexture(_heartTexture);
        _heartTexture = {}; // Zera, para uma segunda chamada não fazer nada
    }
}

// Desenha a vida do jogador no canto superior esquerdo
void Hud::draw(const Player &player) const
{
    int health = player.getHealth();
    int maxHealth = player.getMaxHealth();
    float ratio = (maxHealth > 0) ? (float)health / (float)maxHealth : 0.0f; // Fração da vida, de 0 a 1

    // Ícone do coração
    if (_heartTexture.id != 0)
    {
        float scale = ICON_SIZE / (float)_heartTexture.width; // Ajusta o sprite para o tamanho do ícone
        DrawTextureEx(_heartTexture, Vector2{ MARGIN, MARGIN }, 0.0f, scale, WHITE);
    }
    else
    {
        drawHeartShape(Vector2{ MARGIN + ICON_SIZE / 2.0f, MARGIN + ICON_SIZE / 2.0f }, ICON_SIZE, RED); // Placeholder
    }

    // Barra de vida, ao lado do ícone
    Rectangle bar = { MARGIN + ICON_SIZE + 12.0f, MARGIN + (ICON_SIZE - BAR_HEIGHT) / 2.0f, BAR_WIDTH, BAR_HEIGHT };
    DrawRectangleRec(bar, Fade(BLACK, 0.6f)); // Fundo da barra
    DrawRectangleRec(Rectangle{ bar.x, bar.y, bar.width * ratio, bar.height }, Color{ 200, 40, 50, 255 }); // Parte cheia
    DrawRectangleLinesEx(bar, 2.0f, WHITE); // Borda

    // Texto "vida / vida máxima" centralizado na barra
    const char *text = TextFormat("%d / %d", health, maxHealth);
    int fontSize = 16;
    int textWidth = MeasureText(text, fontSize);
    DrawText(text, (int)(bar.x + (bar.width - textWidth) / 2.0f), (int)(bar.y + (bar.height - fontSize) / 2.0f), fontSize, WHITE);
}
