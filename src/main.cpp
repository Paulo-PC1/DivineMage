#include "raylib.h"
#include "entities/player/player.hpp"
#include "core/animation/animation.hpp"
#include "core/camera/camera.hpp"
#include <iostream>
//--------------------------------------------------------
// Estruturas e Constantes do Programa
//--------------------------------------------------------
const int SCREEN_WIDTH = 1280; // Constantes para representar a tela e evitar numeros mágicos (subtituir por config.hpp)
const int SCREEN_HEIGHT = 720; // Constantes para representar a tela e evitar numeros mágicos (subtituir por config.hpp)

//--------------------------------------------------------
// Funçoes do Programa
//--------------------------------------------------------

//--------------------------------------------------------
// Entrada principal do programa
//--------------------------------------------------------
int main(void)
{
    // Inicializa a tela
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DivineMage"); // Inicializa a janela do jogo com largura 1280, altura 720 e título "DivineMage"
    SetTargetFPS(60); // Define a taxa de quadros por segundo (FPS) para 60, garantindo uma atualização suave da tela e dos elementos do jogo.
 
    Player player (640.0f, 360.0f, 60.0f); // Cria o jogador (posição x, posição y, velocidade)
    GameCamera camera ( // Cria a camera (ponto do mundo que a camera aponta, onde o ponto do mundo que a camera aponta vai ser renderizado na tela, rotação da camera, zoom da camera)
        player.getCenter(), // Define o ponto do mundo que a camera aponta para o ponto do jogador
        { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f}, // Define onde o ponto do mundo que a camera aponta vai ser renderizado na tela (centro da tela)
        0.0f, // Define a rotação da camera (0 graus)
        3.0f // Define o zoom da camera (3.0f = com zoom)
    );
    
    // Loop principal do programa
    while(!WindowShouldClose()){
 
        float dt = GetFrameTime(); // Tempo de atualização do frame
 
        // Atualiza as variaveis do jogo
        player.update(dt); // atualiza a posiçao do jogador 
        camera.follow(player.getCenter()); // atualiza a posição da camera para seguir o jogador
 
        // Desenha na tela
        BeginDrawing(); // inicia o desenho na tela
        ClearBackground(RAYWHITE); // Limpa a tela com a cor selecionada
        
        BeginMode2D(camera.get()); // inicio do modo 2D com a camera definida
            DrawText("DivineMage", SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 20, BLACK); // Desenha o texto na tela
            player.draw(); // Desenha o jogador na tela    
        EndMode2D(); // fim do modo 2D com a camera definida
        
        DrawText("Vida: 100", 10, 10, 20, BLACK); // Desenha o texto na tela (Exemplo de HUD)
        
        EndDrawing(); // Encerra o desenho na tela e troca os buffers (double buffering)
    }
 
    //Descarregar a textura do jogador carregada
    player.unload();
 
    // Fecha a tela
    CloseWindow();
 
    return 0;
}
