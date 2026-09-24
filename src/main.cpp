#include "raylib.h"
#include "entities/player/player.h"
#include "core/animation/animation.h"
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
