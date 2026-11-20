// DivineMage - Shooter/src/rooms/world/world.cpp
#include "rooms/world/world.hpp" // Inclui o cabeçalho da classe World
#include "entities/player/player.hpp" // Definição completa de Player (o world.hpp só tem a declaração antecipada)

// Constantes que só este arquivo usa (o namespace sem nome as esconde do resto do projeto)
namespace {

    constexpr const char *TILESET = ASSETS_PATH "tilesets/dungeon_tiles.png"; // O mesmo tileset serve para as 3 salas (cores diferentes)
    constexpr const char *MAP_ROOM_1    = ASSETS_PATH "maps/room1.json";
    constexpr const char *MAP_ROOM_2    = ASSETS_PATH "maps/room2.json";
    constexpr const char *MAP_ROOM_BOSS = ASSETS_PATH "maps/room_boss.json";

    // Índices das salas dentro do array
    constexpr int ROOM_1    = 0;
    constexpr int ROOM_2    = 1;
    constexpr int ROOM_BOSS = 2;

    // Todas as salas têm 20 x 12 tiles de 32 px. A porta é o tile de vão na parede (coluna 0 ou 19, linha 5)
    constexpr float DOOR_Y = 160.0f;       // 5 * 32: a linha do vão
    constexpr float LEFT_DOOR_X = 0.0f;    // Coluna 0
    constexpr float RIGHT_DOOR_X = 608.0f; // 19 * 32: coluna 19
    constexpr float DOOR_SIZE = 32.0f;     // Um tile

    // Onde o jogador aparece depois de passar por uma porta (canto superior esquerdo do sprite)
    // Fica a 2 tiles de distância da porta, para não encostar nela de novo assim que chega
    constexpr float SPAWN_LEFT_X  = 64.0f;   // Logo depois da porta da esquerda
    constexpr float SPAWN_RIGHT_X = 544.0f;  // Logo antes da porta da direita
    constexpr float SPAWN_Y = 160.0f;        // Na linha das portas
}

// Construtor: começa na primeira sala (as salas do array já foram criadas vazias)
World::World() :
    _currentRoom(ROOM_1)
{
    // Nada a fazer aqui: tudo já foi inicializado na lista acima
}

// Carrega as 3 salas e monta o conteúdo de cada uma (inimigos, portas e loot)
bool World::load()
{
    // ------------------------------------------------------ Sala 1 (inicial)
    if (!_rooms[ROOM_1].load(MAP_ROOM_1, TILESET))
    {
        return false;
    }
    _rooms[ROOM_1].setPlayerSpawn(Vector2{ 320.0f, 192.0f }); // Onde o jogador começa o jogo
    _rooms[ROOM_1].addEnemy(460.0f, 90.0f);
    _rooms[ROOM_1].addEnemy(470.0f, 250.0f);
    _rooms[ROOM_1].addDoor(Door(Rectangle{ RIGHT_DOOR_X, DOOR_Y, DOOR_SIZE, DOOR_SIZE }, ROOM_2, Vector2{ SPAWN_LEFT_X, SPAWN_Y }));
    _rooms[ROOM_1].addLoot(Pickup(300.0f, 170.0f)); // Poção que aparece ao limpar a sala

    // ------------------------------------------------------ Sala 2
    if (!_rooms[ROOM_2].load(MAP_ROOM_2, TILESET))
    {
        return false;
    }
    _rooms[ROOM_2].setPlayerSpawn(Vector2{ SPAWN_LEFT_X, SPAWN_Y });
    _rooms[ROOM_2].addEnemy(320.0f, 64.0f);
    _rooms[ROOM_2].addEnemy(500.0f, 200.0f);
    _rooms[ROOM_2].addEnemy(260.0f, 260.0f);
    _rooms[ROOM_2].addDoor(Door(Rectangle{ LEFT_DOOR_X, DOOR_Y, DOOR_SIZE, DOOR_SIZE }, ROOM_1, Vector2{ SPAWN_RIGHT_X, SPAWN_Y }));
    _rooms[ROOM_2].addDoor(Door(Rectangle{ RIGHT_DOOR_X, DOOR_Y, DOOR_SIZE, DOOR_SIZE }, ROOM_BOSS, Vector2{ SPAWN_LEFT_X, SPAWN_Y }));
    _rooms[ROOM_2].addLoot(Pickup(300.0f, 170.0f));

    // ------------------------------------------------------ Sala do mini-boss
    if (!_rooms[ROOM_BOSS].load(MAP_ROOM_BOSS, TILESET))
    {
        return false;
    }
    _rooms[ROOM_BOSS].setPlayerSpawn(Vector2{ SPAWN_LEFT_X, SPAWN_Y });
    _rooms[ROOM_BOSS].addBoss(400.0f, 140.0f);
    _rooms[ROOM_BOSS].addDoor(Door(Rectangle{ LEFT_DOOR_X, DOOR_Y, DOOR_SIZE, DOOR_SIZE }, ROOM_2, Vector2{ SPAWN_RIGHT_X, SPAWN_Y }));

    _currentRoom = ROOM_1;
    return true;
}

// Libera as 3 salas
void World::unload()
{
    for (int i = 0; i < ROOM_COUNT; ++i)
    {
        _rooms[i].unload();
    }
}

// Atualiza a sala atual e troca de sala se o jogador tocar numa porta destrancada
void World::update(float dt, Player &player)
{
    _rooms[_currentRoom].update(dt, player);

    const Door *door = _rooms[_currentRoom].getDoorTouching(player.getHitbox()); // nullptr se não tocou em nenhuma
    if (door != nullptr)
    {
        changeRoom(door->getTargetRoom(), door->getSpawnInTarget(), player);
    }
}

// Desenha a sala atual
void World::draw() const
{
    _rooms[_currentRoom].draw();
}

// A sala em que o jogador está agora (a GameScreen precisa das paredes e dos projéteis)
Room &World::getCurrentRoom()
{
    return _rooms[_currentRoom];
}

// O chefe foi derrotado? (dispara a tela de créditos)
bool World::isBossDefeated() const
{
    return _rooms[ROOM_BOSS].isBossDefeated();
}

// Muda para outra sala e coloca o jogador na posição de chegada
void World::changeRoom(int index, Vector2 spawn, Player &player)
{
    if (index < 0 || index >= ROOM_COUNT)
    {
        return; // Índice inválido: ignora (protege contra um erro de digitação ao montar as salas)
    }

    _rooms[_currentRoom].clearProjectiles(); // Nenhum tiro fica "congelado" na sala que ficou para trás
    _currentRoom = index;
    player.setPosition(spawn.x, spawn.y); // Método do Entity
}
