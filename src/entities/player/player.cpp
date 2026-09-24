#include "player.h"

// Carrega a textura do jogador, redimensiona e inverte a imagem se necessário
Texture2D loadPlayerTexture(const char *filePath, bool flipHorizontal){
    Image img = LoadImage(filePath); // Carrega a imagem do jogador
    int newWidth = static_cast<int>(img.width * 3); // Aumenta a largura da imagem em 3 vezes
    int newHeigth = static_cast<int>(img.height * 3); // Aumenta a altura da imagem em 3 vezes
    if(flipHorizontal){
        ImageFlipHorizontal(&img); // Inverte a imagem horizontalmente para que o jogador ande para esquerda
    }
    ImageResizeNN(&img, newWidth, newHeigth); // Redimensiona a imagem do jogador
    Texture2D texture = LoadTextureFromImage(img); // Carrega a textura do jogador
    UnloadImage(img); // Descarrega a imagem do jogador da memoria
    return texture; // Retorna a textura do jogador
}

// Cria o jogador com posição inicial, velocidade e textura inicial
Player initPlayer(float x, float y, float speed)
{
    Player player;
    player.x = x; // Posição inicial do jogador no eixo x
    player.y = y; // Posição inicial do jogador no eixo y
    player.oldPos = { x, y }; // Posição inicial do jogador
    player.speed = speed; // Velocidade do jogador
    player.texture = loadPlayerTexture("../../assets/sprites/Player.png", false); // Carrega a textura do jogador
    return player;
}

// Atualiza o movimento e a textura do jogador
void updatePlayer(Player &player, float dt)
{
    if(IsKeyDown(KEY_W)) player.y -= player.speed * dt; // Se a tecla W estiver pressionada, o jogador se move para cima
    if(IsKeyDown(KEY_S)) player.y += player.speed * dt; // Se a tecla S estiver pressionada, o jogador se move para baixo
    if(IsKeyDown(KEY_A)){ // Se a tecla A estiver pressionada, o jogador se move para esquerda
        player.x -= player.speed * dt; // Se a tecla A estiver pressionada, o jogador se move para esquerda
        UnloadTexture(player.texture); // Descarrega a textura do jogador
        player.texture = loadPlayerTexture("../../assets/sprites/player_walking.png", true); // Carrega a imagem do jogador andando para esquerda (invertida)
    }
    if(IsKeyDown(KEY_D)) { // Se a tecla D estiver pressionada, o jogador se move para direita
        player.x += player.speed * dt; // Se a tecla D estiver pressionada, o jogador se move para direita
        UnloadTexture(player.texture); // Descarrega a textura do jogador
        player.texture = loadPlayerTexture("../../assets/sprites/player_walking.png", false); // Carrega a imagem do jogador andando
    }
    if(player.oldPos.x == player.x && player.oldPos.y == player.y){ // Se a posição do jogador não mudou, significa que ele parou de se mover
        UnloadTexture(player.texture); // Descarrega a textura do jogador
        player.texture = loadPlayerTexture("../../assets/sprites/Player.png", false); // Carrega a imagem do jogador
    }
 
    player.oldPos = { player.x, player.y }; // Atualiza a posição antiga do jogador
}

// Desenha o jogador na tela
void drawPlayer(const Player &player, const Animation &anim)
{
    DrawTextureRec(player.texture, anim.frameRec, Vector2{ player.x, player.y }, WHITE); // Desenha a textura do jogador na posição
}
 
// Descarrega a textura do jogador
void unloadPlayer(Player &player)
{
    UnloadTexture(player.texture);
}