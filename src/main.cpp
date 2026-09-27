#include "raylib.h"
#include "entities/player/player.h"
#include "core/animation/animation.h"
#include "core/camera/camera.h"
#include <iostream>
//--------------------------------------------------------
// Estruturas e Funções do Programa
//--------------------------------------------------------

//--------------------------------------------------------
// Funçoes do Programa
//--------------------------------------------------------

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
    Camera2D camera = initCamera( // Cria a camera (ponto do mundo que a camera aponta, onde o ponto do mundo que a camera aponta vai ser renderizado na tela, rotação da camera, zoom da camera)
        { player.x, player.y }, // Define o ponto do mundo que a camera aponta para o ponto do jogador
        { 1280.0f / 2, 720.0f / 2}, // Define onde o ponto do mundo que a camera aponta vai ser renderizado na tela (centro da tela)
        0.0f, // Define a rotação da camera (0 graus)
        1.0f // Define o zoom da camera (1.0f = sem zoom)
    );
    
    // Loop principal do programa
    while(!WindowShouldClose()){
 
        float dt = GetFrameTime(); // Tempo de atualização do frame
 
        // Atualiza as variaveis do jogo
        updatePlayer(player, dt); // atualiza a posiçao do jogador 
        updateAnimation(anim, dt); // atualiza a animação 
        updateCameraFollow(camera, {player.x, player.y}); // atualiza a posição da camera para seguir o jogador
 
        // Desenha na tela
        BeginDrawing(); // inicia o desenho na tela
        ClearBackground(RAYWHITE); // Limpa a tela com a cor selecionada
        
        BeginMode2D(camera); // inicio do modo 2D com a camera definida
            DrawText("DivineMage", 640, 360, 20, BLACK); // Desenha o texto na tela
            drawPlayer(player, anim); // Desenha o jogador na tela
            
        EndMode2D(); // fim do modo 2D com a camera definida
        DrawText("Vida: 100", 10, 10, 20, BLACK); // Desenha o texto na tela (Exemplo de HUD)
        EndDrawing(); // Encerra o desenho na tela e troca os buffers (double buffering)
    }
 
    //Descarregar a textura do jogador carregada
    unloadPlayer(player);
 
    // Fecha a tela
    CloseWindow();
 
    return 0;
}
