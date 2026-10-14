//DivineMage - Shooter/src/main.cpp
#include "raylib.h" // Inclui a biblioteca Raylib para manipulação de gráficos e entrada do usuário
#include "core/game/game.hpp" // Inclui a classe Game para gerenciar o estado do jogo, incluindo a janela, a tela atual e o loop principal do jogo.

// Função principal do jogo, responsável por criar uma instância da classe Game e iniciar o loop principal do jogo.
int main(void)
{
    Game game; // Cria uma instância da classe Game, responsável por gerenciar o estado do jogo, incluindo a janela, a tela atual e o loop principal do jogo.
    game.run(); // Inicia o loop principal do jogo, onde serão atualizados e desenhados os elementos do jogo a cada frame.
    return 0;
}
