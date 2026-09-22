#include "raylib.h"
#include <iostream>

//--------------------------------------------------------
// Funçoes do Programa
//--------------------------------------------------------

//--------------------------------------------------------
// Entrada principal do programa
//--------------------------------------------------------
int main(void)
{   
    // Inicializa a tela
    InitWindow(800, 600, "DivineMage"); // Inicializa a janela do jogo com largura 800, altura 600 e título "DivineMage"
    SetTargetFPS(60); // Define a taxa de quadros por segundo (FPS) para 60, garantindo uma atualização suave da tela e dos elementos do jogo.
    
    float x = 400.0f; // Posição inicial do jogador no eixo x
    float y = 300.0f; // Posição inicial do jogador no eixo y
    Vector2 oldPos = { x, y }; // Posição inicial do jogador
    const float speed = 100.0f; // Velocidade do jogador 
    //Código para carregar textura de um personagem no game (teste com imagem de video tutórial)
    Texture2D jogador; // Variavel para armazenar a textura do jogador
    Image img = LoadImage("../../assets/sprites/Player.png"); // Carrega a imagem do jogador
    int newWidth = static_cast<int>(img.width * 3); // Aumenta a largura da imagem em 3 vezes
    int newHeigth = static_cast<int>(img.height * 3); // Aumenta a altura da imagem em 3 vezes
    ImageResizeNN(&img, newWidth, newHeigth); // Redimensiona a imagem do jogador
    jogador = LoadTextureFromImage(img); // Carrega a textura do jogador a partir da imagem redimensionada
    UnloadImage(img); // Descarrega a imagem do jogador da memoria

    //Para cilcar os sprites dividimos a imagem pelo numero de sprites que eal possui(no caso atual 6)
    int frameWidth = jogador.width / 6; // Largura de cada frame(numero total de frames = 6)
    int frameHeigth = jogador.height; // Altura de cada frame (altura total da imagem)
    Rectangle frameRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeigth }; // Retangulo para definir qual parte ira cortar da imagem
    int currentFrame = 0; // Frame atual
    float frameTime = 0.0f; // Tempo de atualização do frame
    const float updateTime = 0.2f; // Tempo de atualização dos frames
    
    // Loop principal do programa
    while(!WindowShouldClose()){
        
        float dt = GetFrameTime(); // Tempo de atualização do frame
        frameTime += dt; // Acumula o tempo de atualização do frame
        
        // Atualiza as variaveis do jogo
        if(IsKeyDown(KEY_W)) y -= speed * dt; // Se a tecla W estiver pressionada, o jogador se move para cima
        if(IsKeyDown(KEY_S)) y += speed * dt; // Se a tecla S estiver pressionada, o jogador se move para baixo
        if(IsKeyDown(KEY_A)){ // Se a tecla A estiver pressionada, o jogador se move para esquerda
            x -= speed * dt; // Se a tecla A estiver pressionada, o jogador se move para esquerda
            UnloadTexture(jogador); // Descarrega a textura do jogador
            Image img = LoadImage("../../assets/sprites/player_walking.png"); // Carrega a imagem do jogador andando para esquerda
            int newWidth = static_cast<int>(img.width * 3); // Aumenta a largura da imagem em 3 vezes
            int newHeigth = static_cast<int>(img.height * 3); // Aumenta a altura da imagem em 3 vezes
            ImageFlipHorizontal(&img); // Inverte a imagem horizontalmente para que o jogador ande para esquerda
            ImageResizeNN(&img, newWidth, newHeigth); // Redimensiona a imagem do jogador
            jogador = LoadTextureFromImage(img); // Carrega a textura do jogador a partir da imagem redimensionada
            UnloadImage(img); // Descarrega a imagem do jogador da memoria
        }
        if(IsKeyDown(KEY_D)) { // Se a tecla D estiver pressionada, o jogador se move para direita
            x += speed * dt; // Se a tecla D estiver pressionada, o jogador se move para direita
            UnloadTexture(jogador); // Descarrega a textura do jogador
            Image img = LoadImage("../../assets/sprites/player_walking.png"); // Carrega a imagem do jogador andando para esquerda
            int newWidth = static_cast<int>(img.width * 3); // Aumenta a largura da imagem em 3 vezes
            int newHeigth = static_cast<int>(img.height * 3); // Aumenta a altura da imagem em 3 vezes
            ImageResizeNN(&img, newWidth, newHeigth); // Redimensiona a imagem do jogador
            jogador = LoadTextureFromImage(img); // Carrega a textura do jogador a partir da imagem redimensionada
            UnloadImage(img); // Descarrega a imagem do jogador da memoria
        }
        if(oldPos.x == x && oldPos.y == y){ // Se a posição do jogador não mudou, significa que ele parou de se mover
            UnloadTexture(jogador); // Descarrega a textura do jogador
            Image img = LoadImage("../../assets/sprites/Player.png"); // Carrega a imagem do jogador 
            int newWidth = static_cast<int>(img.width * 3); // Aumenta a largura da imagem em 3 vezes
            int newHeigth = static_cast<int>(img.height * 3); // Aumenta a altura da imagem em 3 vezes
            ImageResizeNN(&img, newWidth, newHeigth); // Redimensiona a imagem do jogador
            jogador = LoadTextureFromImage(img); // Carrega a textura do jogador a partir da imagem redimensionada
            UnloadImage(img); // Descarrega a imagem do jogador da memoria
        }
        
        // Atualiza o frame atual se o tempo de atualização do frame for maior ou igual ao tempo definido
        if (frameTime >= updateTime){
            frameTime -= updateTime; // Reseta o tempo de atualização do frame
            currentFrame++; // Incrementa o frame atual
            if (currentFrame >= 6){ // Se o frame atual for maior ou igual ao numero total de frames, reseta o frame atual
                currentFrame = 0; // Reseta o frame atual
            }
            frameRec.x = currentFrame * frameWidth; // Atualiza a posição do retangulo para cortar a imagem
        }
        
        oldPos = { (float)x, (float)y }; // Atualiza a posição antiga do jogador
        
        // Desenha na tela
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawText("DivineMage", 350, 300, 20, BLACK); // Desenha o texto na tela
        DrawTextureRec(jogador, frameRec, Vector2{ (float)x, (float)y}, WHITE); // Desenha a textura do jogador na posição 
        //DrawCircleV(circlePosition, 25.0f, RED);
        EndDrawing(); // Encerra o desenho na tela e troca os buffers (double buffering)
    }
    
    //Descarregar a textura do jogador carregada
    UnloadTexture(jogador);
    
    // Fecha a tela
    CloseWindow();
    
    return 0;
}