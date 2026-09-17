# DivineMage - Magic Shooter/Rouguelite

## Ideia Central do Projeto

Um game onde você é um mago sem forma física que esta preso em uma masmorra e deve enfrentar monstros e chefes para sair desse lugar

## Mecânicas Pensadas e Ideias Gerais

- Personagem Principal Fixo (apenas 1 para game todo)
- 3-4 tipos de Armas(Cajados) com disparos de projéteis diferentes
- 4-6 itens consumiveis (Poções) que modificam tanto os atributos (Vida, Escudo) do personagem como afetam as magias e danos
- 2-4 combinações de poções que geram efeitos na arma (EX: poção de fogo + cajado de fogo = mais 2 disparos ao atacar)
- 3-6 inimigos base para enfrentar durante as salas
- 1-2 Bosses para enfrentar ao final da "run" (Matou Boss volta a tela de Inicio apenas)
- 2-4 salas (sem contar a do Boss) que ao matar todos os inimigos spawna 1 poção ou 1 cajado (aleatório ou pré-definido ainda a decidir).
- Menu com opções: Jogar, Controles, Opções, Créditos e Sair -> detalhamento das opões -> Jogar: ao clicar mostra uma lista na tela dos controles e aguarda jogador apertar [espaço] par continuar e da inicio ao game; Controles: Mostra os controles básicos do game e opção para voltar a tela inicial;; Opções: permite reduzir volume do som geral e música e opção para voltar a tela inicial; Créditos: mostra nome do criador do game, nome de quem fez as artes, nome da diciplina e professor responsável, nome das técnologias, biblieotecas, e assets usados e opção para voltar a tela inicial; Sair: fecha o game instantaniamente;

## Requisitos Funcionais

RF001
Nome: Loop Gameplay
Descrição: Sistema deve possuir loop de gameplay onde jogador começa jogo passa por fasses(cenários) e finalia ao enfrentar Boss
Observação: Deve possuir níumero X de fases e 1 Boss ai final dela que a cada vez que clia em jogar é trocado tudo
Prioridade: ALTA
Complexidade: MÉDIA

RF002
Nome: Loot System
Descrição: Deve possuir sistema de loot(drop) vinculado aos inimigos/fase
Obsevação: Ao matar todos os inimigos da fase(sessão/cenário) é dropado Loot(Bau) referente a Inimigos/Cenário que dão ao jogador 1 poção ou 1 cajado aleatorio que jogador escolhe ou não se quer pegar
Prioridade: ALTA
Complexidade: ALTA

RF003
Nome: World System
Descrição: Deve possuir sistema de fases conectadas onde se pode ir e voltar de cada cenário a qualquer momento antes de finalizar ou perder
Obsevação: Cenários(Tileset) Interconectados uns aos outros que ao finalizar 1x não pode respwnar os inimigos
Prioridade: ALTA
Complexidade: MÉDIA

RF004
Nome: Combine Duplicate Itens
Descrição: Deve permitir que itens duplicados se combinem melhorando de nível mudando seu comportamento
Observação: Cajados repetidos aumentam ou mudam a magia disparada, poções repetidas aumentam seus efeitos
Prioridade: MÉDIA
Complexidade: MÉDIA

RF005
Nome: Build System
Descrição: Deve permitir interação entre Armas(cajados) e Itens(Poções)
Observação: Cajados e poções podem combinar seus efeitos singulares gerando novos efeitos únicos que podem ser passivos ou ativos

RF006
Nome: Enemy System
Descrição: deve possuir sistema de inimigos que atacam o jogador causando dano a ele
Prioridade: ALTA
Complexidade: MÉDIA

RF007
Nome: Weapon System
Descrição: Deve possuir sistema de armas(cajados) e trocas de armas
Observação: O jogador pode ter apenas 1 cajado equipado por vez
Prioridade: ALTA
Complexidade: MÉDIA

RF008
Nome: Boss System
Descrição: Deve possuir Chefes(Boss) finais de cada set de mapas
Observação: O chefe deve ter movimentos únicos e aparencia única e um tamanho maior em comparação aos inimigos comuns e ao jogador
Prioridade: ALTA
Complexidade: MÉDIA

## Requisitos Não Funcionais

RNF001
Nome: Orientação a Objeto
Descrição O jogo deve ser construido seguindo os princípios de orientação a objeto
Observação: Deve seguir os conceitos aprendidos em sala de aula sobre orientação a objetos
Prioridade: ALTA
Complexidade: ALTA

RNF002
Nome: Linguagem e Bibliotecas Utilizada
Descrição: Deve ser feito com C++17 ou superior e com a biblioteca Raylib 5.5 ou superior
Prioridade: ALTA
Complexidade : BAIXA

RNF003
Nome: Facilidade Controles
Descrição: Deve possuir controles faceís de usar
Observação: Opção no menu inicial ou de pause para ver os controles
Prioridade: MÉDIA
Complexidade: BAIXA

RNF004
Nome: Menu
Descrição: Deve ter um menu de navegação simples e facil de se utlizar
Prioridade: MÉDIA
Complexidade: BAIXA
