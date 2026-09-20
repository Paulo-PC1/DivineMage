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
    InitWindow(800, 600, "DivineMage");
    SetTargetFPS(60);
    
    Vector2 circlePosition = { 400.0f, 300.0f }; // Posição inicial do círculo
    
    // Loop principal do programa
    while(!WindowShouldClose()){
        
        // Atualiza as variaveis do jogo
        if(IsKeyDown(KEY_D)) circlePosition.x += 2.0f;
        if(IsKeyDown(KEY_A)) circlePosition.x -= 2.0f;
        if(IsKeyDown(KEY_W)) circlePosition.y -= 2.0f;
        if(IsKeyDown(KEY_S)) circlePosition.y += 2.0f;
        
        // Desenha na tela
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawText("DivineMage", 350, 300, 20, BLACK);
        DrawCircleV(circlePosition, 25.0f, RED);
        EndDrawing();
    }
    
    // Fecha a tela
    CloseWindow();
    
    return 0;
}