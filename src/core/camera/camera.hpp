#pragma once
#include "raylib.h"

class GameCamera {

    public:
        //Construtor, inicializa a câmera com alvo, offset, rotação e zoom
        explicit GameCamera(Vector2 target, Vector2 offset, float rotation, float zoom);

        //Atualiza o alvo da câmera para seguir uma posição (ex: o jogador)
        void follow(Vector2 target);

        //Getter: devolve a Camera2D "crua" do raylib, pronta pra BeginMode2D
        Camera2D get() const;

    private:

        Camera2D _camera;
};