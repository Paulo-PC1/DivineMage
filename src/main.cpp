#include "raylib.h"
#include <iostream>
//--------------------------------------------------------
// Estruturas e Funções do Programa
//--------------------------------------------------------
struct Player {
    float x; // Posição do jogador no eixo x
    float y; // Posição do jogador no eixo y
    Vector2 oldPos; // Posição antiga do jogador
    float speed; // Velocidade do jogador
    Texture2D texture; // Textura do jogador
};

struct Animation {
    int totalFrames; // Número total de frames da animação
    int frameWidth; // Largura de cada frame
    int frameHeigth; // Altura de cada frame (altura total da imagem)
    Rectangle frameRec; // Retangulo para definir qual parte ira cortar da imagem
    int currentFrame; // Frame atual
    float frameTime; // Tempo de atualização do frame
    float updateTime; // Tempo de atualização dos frames
};

//--------------------------------------------------------
// Funçoes do Programa
//--------------------------------------------------------

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
// Cria a animação dividindo a textura pelo numero de sprites que ela possui
Animation initAnimation(const Texture2D &texture, int totalFrames, float updateTime)
{
    Animation anim;
    anim.totalFrames = totalFrames; // Numero total de frames
    anim.frameWidth = texture.width / totalFrames; // Largura de cada frame
    anim.frameHeigth = texture.height; // Altura de cada frame (altura total da imagem)
    anim.frameRec = { 0.0f, 0.0f, (float)anim.frameWidth, (float)anim.frameHeigth }; // Retangulo para definir qual parte ira cortar da imagem
    anim.currentFrame = 0; // Frame atual
    anim.frameTime = 0.0f; // Tempo de atualização do frame
    anim.updateTime = updateTime; // Tempo de atualização dos frames
    return anim;
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
 
// Atualiza o frame atual se o tempo de atualização do frame for maior ou igual ao tempo definido
void updateAnimation(Animation &anim, float dt)
{
    anim.frameTime += dt; // Acumula o tempo de atualização do frame
 
    if (anim.frameTime >= anim.updateTime){
        anim.frameTime -= anim.updateTime; // Reseta o tempo de atualização do frame
        anim.currentFrame++; // Incrementa o frame atual
        if (anim.currentFrame >= anim.totalFrames){ // Se o frame atual for maior ou igual ao numero total de frames, reseta o frame atual
            anim.currentFrame = 0; // Reseta o frame atual
        }
        anim.frameRec.x = anim.currentFrame * anim.frameWidth; // Atualiza a posição do retangulo para cortar a imagem
    }
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

//--------------------------------------------------------
// Entrada principal do programa
//--------------------------------------------------------
int main(void)
{
    // Inicializa a tela
    InitWindow(1280, 720, "DivineMage"); // Inicializa a janela do jogo com largura 800, altura 600 e título "DivineMage"
    SetTargetFPS(60); // Define a taxa de quadros por segundo (FPS) para 60, garantindo uma atualização suave da tela e dos elementos do jogo.
 
    Player player = initPlayer(640.0f, 360.0f, 100.0f); // Cria o jogador (posição x, posição y, velocidade)
    Animation anim = initAnimation(player.texture, 6, 0.2f); // Cria a animação (textura, numero de frames, tempo de atualização)
 
    // Loop principal do programa
    while(!WindowShouldClose()){
 
        float dt = GetFrameTime(); // Tempo de atualização do frame
 
        // Atualiza as variaveis do jogo
        updatePlayer(player, dt);
        updateAnimation(anim, dt);
 
        // Desenha na tela
        BeginDrawing();
        ClearBackground(RAYWHITE);
 
        DrawText("DivineMage", 640, 360, 20, BLACK); // Desenha o texto na tela
        drawPlayer(player, anim);
        EndDrawing(); // Encerra o desenho na tela e troca os buffers (double buffering)
    }
 
    //Descarregar a textura do jogador carregada
    unloadPlayer(player);
 
    // Fecha a tela
    CloseWindow();
 
    return 0;
}
