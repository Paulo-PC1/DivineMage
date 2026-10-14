//DivineMAge - Shooter/src/screens/game_screen/game_screen.hpp
#pragma once // Diretiva de pré-processador para evitar múltiplas inclusões do mesmo arquivo    
#include "screens/screen/screen.hpp" // Inclui a classe Screen para gerenciar a tela do jogo
#include "entities/player/player.hpp" // Inclui a classe Player para gerenciar o jogador do jogo
#include "core/camera/camera.hpp" // Inclui a classe Camera para gerenciar a câmera do jogo

// Classe GameScreen: Essa classe representa a tela de gameplay do jogo, onde o jogador controla o personagem e interage com o ambiente. Ela herda da classe Screen e implementa os métodos update e draw para atualizar e desenhar os elementos da tela de gameplay.
class GameScreen : public Screen {

public:
    GameScreen();
    
    ~GameScreen() override;
    
    ScreenType update(float dt) override; // Atualiza o estado da tela de gameplay, incluindo a lógica de movimentação, colisões e outros elementos. O parâmetro dt representa o tempo de atualização do frame (delta time).
    
    void draw() override; // Desenha os elementos da tela de gameplay na tela, incluindo o jogador, inimigos, cenário e HUD.   
    
private:
    Player _player; // Instancia da classe Player para gerenciar o jogador do jogo, incluindo sua posição, velocidade e animações.
    GameCamera _camera; // Instancia da classe GameCamera para gerenciar a câmera do jogo, incluindo sua posição e orientação.
};