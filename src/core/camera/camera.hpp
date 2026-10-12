//DivineMage - Shooter/src/core/camera/camera.hpp
#pragma once // Diretiva de pré-processador para evitar múltiplas inclusões do mesmo arquivo
#include "raylib.h" // Inclui a biblioteca Raylib para manipulação de gráficos e entrada do usuário

// Classe GameCamera representa a câmera do jogo, incluindo seu alvo, offset, rotação e zoom
class GameCamera {

    public:
        //Construtor, inicializa a câmera com alvo, offset, rotação e zoom
        explicit GameCamera(Vector2 target, Vector2 offset, float rotation, float zoom);

        //Atualiza o alvo da câmera para seguir uma posição (ex: o jogador)
        void follow(Vector2 target);

        //Getter: devolve a Camera2D "crua" do raylib, pronta pra BeginMode2D
        Camera2D get() const;

    private:

        Camera2D _camera; // Camera2D do raylib, que contém as propriedades da câmera (offset, target, rotation, zoom)
};