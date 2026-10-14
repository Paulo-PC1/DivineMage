// DivineGame - Shooter/src/core/game/game.hpp
#pragma once // Diretiva de pré-processador para evitar múltiplas inclusões do mesmo arquivo
#include "screens/screen/screen.hpp" // Inclui a classe Screen para gerenciar a tela do jogo

class Game {
    
public:
    //Construtor da classe Game
    Game(); // Construtor da classe Game, responsável por inicializar a janela do jogo e definir a taxa de quadros por segundo (FPS).
    
    ~Game(); // Destrutor da classe Game, responsável por fechar a janela do jogo e liberar recursos alocados.
    
    Game(const Game &) = delete; // Desabilita o construtor de cópia da classe Game, evitando cópias indesejadas do objeto Game.
    Game &operator=(const Game &) = delete; // Desabilita o operador de atribuição da classe Game, evitando cópias indesejadas do objeto Game.
    
    void run(); // Função para iniciar o loop do jogo, onde serão atualizados e desenhados os elementos do jogo a cada frame.
    
private:
    void update(float dt); // Função para atualizar o estado do jogo, incluindo a lógica de movimentação, colisões e outros elementos.
    void draw(); // Função para desenhar os elementos do jogo na tela, incluindo o jogador, inimigos, cenário e HUD.    
    void changeScreen(ScreenType screenType); // Função para mudar a tela atual do jogo, permitindo transições entre diferentes estados do jogo (ex: menu, gameplay, pause).
    
    Screen* _currentScreen; // Ponteiro para a tela atual do jogo, permitindo o gerenciamento de diferentes estados do jogo.
    bool _shouldClose; // Variável para verificar se a janela do jogo deve ser fechada, controlando o loop principal do jogo.
    
};
