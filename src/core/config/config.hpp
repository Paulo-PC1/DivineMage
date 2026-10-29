// src/core/config/config.hpp
#pragma once

// Namespace Config: Esse namespace contém constantes de configuração do jogo, como dimensões da tela, 
//taxa de quadros por segundo (FPS), título da janela, tamanho dos tiles e sprites, zoom da câmera e tempo máximo de atualização do frame. 
//Essas constantes são usadas em todo o código do jogo para garantir consistência e facilitar ajustes futuros.
namespace Config {
    
    // Janela do jogo
    constexpr int SCREEN_WIDTH = 1280; // Constantes para representar a tela e evitar numeros mágicos
    constexpr int SCREEN_HEIGHT = 720; // Constantes para representar a tela e evitar numeros
    constexpr int TARGET_FPS = 60; // Constante para definir a taxa de quadros por segundo (FPS)
    constexpr const char* WINDOW_TITLE = "DivineMage"; // Constante para definir o título da janela do jogo
    
    //Mundo 
    constexpr float TILE_SIZE = 32.0f; // Constante para definir o tamanho do tile (32 pixels)
    constexpr float CAMERA_ZOOM = 3.0f; // Constante para definir o zoom da camera (3.0f = com zoom)
    constexpr float MAX_DT = 0.05f; // Constante para definir o tempo máximo de atualização do frame (0.05 segundos = 20 FPS)
    
    //Sprites
    constexpr int SPRITE_SIZE = 32; // Constante para definir o tamanho do sprite (32 pixels)
    constexpr int BOSS_SIZE = 64; // Constante para definir o tamanho do boss (64 pixels)
}