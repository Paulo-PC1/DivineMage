#pragma once
#include "raylib.h"
#include "core/animation/animation.hpp"

class Player {
    
    public:
        //Construtor, cria o jogador com posição inicial, velocidade e textura inicial
        explicit Player(float x, float y, float speed);
        
        //Atualiza o movimento e a textura do jogador
        void update (float dt);
        
        //Desenha o jogador na tela
        void draw(const Animation &anim) const;
        
        //Descarrega a textura do jogador
        void unload();
        
        //Getters
        float getX() const;
        float getY() const;
        Texture2D getTexture() const;
    
    private:
    
        Texture2D loadTexture(const char *filePath, bool flipHorizontal); // Carrega a textura do jogador, redimensiona e inverte a imagem se necessário
    
        float _x; // Posição do jogador no eixo x
        float _y; // Posição do jogador no eixo y
        Vector2 _oldPos; // Posição antiga do jogador
        float _speed; // Velocidade do jogador
        Texture2D _texture; // Textura do jogador
};

