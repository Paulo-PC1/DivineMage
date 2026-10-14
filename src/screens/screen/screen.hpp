// DivineMage - Shooter/src/screens/screen/screen.hpp
#pragma once // Diretiva de pré-processador para evitar múltiplas inclusões do mesmo arquivo

// Enumeração ScreenType representa os diferentes tipos de telas do jogo, permitindo a identificação e gerenciamento das telas durante a execução do jogo.
enum class ScreenType {
    MAIN_MENU, // Tela do menu principal do jogo
    GAMEPLAY, // Tela de gameplay do jogo
    CREDITS, // Tela de créditos do jogo
    GAME_OVER, // Tela de game over do jogo
    EXIT,// Tela de saída do jogo
    NONE // Valor padrão para indicar que não há tela selecionada
};

class Screen {
public:
    
    virtual ~Screen() = default; // Destrutor virtual padrão para permitir a destruição correta de objetos derivados da classe Screen.
    
    virtual ScreenType update(float dt) = 0; // Método virtual puro para atualizar o estado da tela, incluindo a lógica de movimentação, colisões e outros elementos. O parâmetro dt representa o tempo de atualização do frame (delta time).
    
    virtual void draw() = 0; // Método virtual puro para desenhar os elementos da tela na tela, incluindo o jogador, inimigos, cenário e HUD.
};