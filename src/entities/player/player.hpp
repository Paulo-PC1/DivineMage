// DivineMage - Shooter/src/entities/player/player.hpp
#pragma once // Diretiva de pré-processador para evitar múltiplas inclusões do mesmo arquivo
#include "entities/actor/actor.hpp" // Inclui a classe Actor, que é a classe base para o jogador
#include "core/animation/animation.hpp" // Inclui a classe Animation para gerenciar animações do jogador
#include "weapons/staff/staff.hpp" // Inclui a classe Staff para gerenciar armas do jogador
#include "weapons/projectile/projectile.hpp" // Inclui a classe Projectile para gerenciar projéteis disparados pelo jogador

// Classe Player representa o jogador no jogo, incluindo sua posição, velocidade, textura e animações
class Player : public Actor {
    
    public:
        //Construtor, cria o jogador com posição inicial, velocidade e textura inicial
        explicit Player(float x, float y, float speed);
        
        //Atualiza o movimento e a textura do jogador
        void update(float dt, const std::vector<Rectangle> &walls) override;
        
        //Desenha o jogador na tela
        void draw() const override;
        
        //Descarrega a textura do jogador
        void unload();
        
        // A GameScreen converte o mouse para coordenadas do mundo (precisa da câmera)
        void shoot(Vector2 aimWorldPosition, std::vector<Projectile> &projectiles);
        
    private:
    
        Texture2D loadTexture(const char *filePath); // Carrega a textura do jogador
                
        bool _facingLeft; // Variavel para verificar se jogador está olhando para esquerda
        bool _isMoving; // Variável para verificar se ogador está se movimentando
        bool _wasMoving; // Variavel para verificar se o jogador esta se movendo
        Texture2D _idleTexture; // Textura do jogador parado (carrega Player.png 1 vez só)
        Texture2D _walkTexture; // Textura do jogador andando (carrega player_walking.png 1 vez só, sempre olhando para direita)
        Animation _idleAnim; // Animação do jogador parado (carrega Player.png 1 vez só)
        Animation _walkAnim; // Animação do jogador andando (carrega player_walking.png 1 vez só, sempre olhando para direita)
        Staff _staff; // Arma do jogador (carrega staff.png 1 vez só)        
};

