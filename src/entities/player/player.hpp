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
        float _speed; // Velocidade do jogador
        Texture2D _idleTexture; // Textura do jogador parado (carrega Player.png 1 vez só)
        Texture2D _walkTexture; // Textura do jogador andando (carrega player_walking.png 1 vez só, sempre olhando para direita)
        bool _facingLeft; // Variavel para verificar se jogador está olhando para esquerda
        bool _isMoving; // Variável para verificar se ogador está se movimentando
        
};

