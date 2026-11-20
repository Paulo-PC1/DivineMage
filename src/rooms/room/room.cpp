// DivineMage - Shooter/src/rooms/room/room.cpp
#include "rooms/room/room.hpp" // Inclui o cabeçalho da classe Room
#include "entities/player/player.hpp" // Definição completa de Player (o room.hpp só tem a declaração antecipada)

// Caminhos dos sprites e funções auxiliares que só este arquivo usa (o namespace sem nome as esconde do resto do projeto)
namespace {

    // PLACEHOLDERS: crie estes PNGs no Aseprite quando quiser trocar os retângulos coloridos por arte.
    // Enquanto o arquivo não existir, o jogo desenha formas simples no lugar (e não dá erro).
    constexpr const char *ENEMY_SPRITE  = ASSETS_PATH "sprites/enemies/Enemy_Walk.png";   // Folha horizontal de frames 32x32
    constexpr const char *BOSS_SPRITE   = ASSETS_PATH "sprites/enemies/Boss_Walk.png";    // Folha horizontal de frames 64x64
    constexpr const char *DOOR_SPRITE   = ASSETS_PATH "sprites/props/Door.png";           // 2 frames de 32x32: fechada e aberta
    constexpr const char *POTION_SPRITE = ASSETS_PATH "sprites/items/Health_Potion.png";  // 1 frame de 32x32

    // Carrega um sprite SE o arquivo existir. Se não existir, devolve uma textura zerada (id = 0), sem erro no console
    Texture2D loadSprite(const char *filePath)
    {
        Texture2D texture = {};  // Textura vazia (id = 0)
        if (FileExists(filePath)) // O arquivo já foi criado?
        {
            texture = LoadTexture(filePath);
            SetTextureFilter(texture, TEXTURE_FILTER_POINT); // Pixels nítidos, igual ao jogador
        }
        return texture;
    }

    // Descarrega uma textura (se houver) e a zera, para uma segunda chamada não fazer nada
    void unloadSprite(Texture2D &texture)
    {
        if (texture.id != 0)
        {
            UnloadTexture(texture);
            texture = {};
        }
    }
}

// Construtor: zera tudo (as texturas começam vazias, o que permite ao World criar um array de Room)
Room::Room() :
    _enemyTexture{},
    _bossTexture{},
    _doorTexture{},
    _potionTexture{},
    _playerSpawn{ 0.0f, 0.0f },
    _cleared(false)
{
    // Nada a fazer aqui: os vetores e o TileMap já nascem vazios
}

// Destrutor: garante que as texturas sejam liberadas
Room::~Room()
{
    unload();
}

// Carrega o mapa e os sprites. Devolve false se o MAPA falhar (sprites ausentes não são erro)
bool Room::load(const std::string &mapPath, const std::string &tilesetPath)
{
    if (!_tilemap.load(mapPath, tilesetPath))
    {
        TraceLog(LOG_ERROR, "Room: nao carregou o mapa %s", mapPath.c_str());
        return false;
    }

    _enemyTexture  = loadSprite(ENEMY_SPRITE);
    _bossTexture   = loadSprite(BOSS_SPRITE);
    _doorTexture   = loadSprite(DOOR_SPRITE);
    _potionTexture = loadSprite(POTION_SPRITE);

    rebuildCollisionRects(); // Monta a lista de colisão com as paredes do mapa
    return true;
}

// Libera tudo que a sala carregou
void Room::unload()
{
    // Os inimigos, portas e itens guardam o ENDEREÇO das texturas, então são apagados antes delas
    _enemies.clear();
    _bosses.clear();
    _doors.clear();
    _loot.clear();
    _playerProjectiles.clear();
    _enemyProjectiles.clear();

    unloadSprite(_enemyTexture);
    unloadSprite(_bossTexture);
    unloadSprite(_doorTexture);
    unloadSprite(_potionTexture);

    _tilemap.unload();
}

// Adiciona um inimigo comum na posição indicada (canto superior esquerdo do sprite)
void Room::addEnemy(float x, float y)
{
    _enemies.emplace_back(x, y, _enemyTexture); // Cria o inimigo direto dentro do vetor
}

// Adiciona o chefe na posição indicada
void Room::addBoss(float x, float y)
{
    _bosses.emplace_back(x, y, _bossTexture);
}

// Adiciona uma porta (ela já nasce trancada)
void Room::addDoor(const Door &door)
{
    _doors.push_back(door); // Guarda uma cópia da porta no vetor
    _doors.back().setTexture(&_doorTexture); // A cópia passa a usar a textura da sala
    rebuildCollisionRects(); // Porta trancada é parede, então a lista de colisão muda
}

// Adiciona um item de loot (ele só aparece quando a sala é limpa)
void Room::addLoot(const Pickup &loot)
{
    _loot.push_back(loot);
    _loot.back().setTexture(&_potionTexture);
}

void Room::setPlayerSpawn(Vector2 spawn)
{
    _playerSpawn = spawn;
}

// Atualiza a sala inteira, em uma ordem que evita bugs (veja cada etapa abaixo)
void Room::update(float dt, Player &player)
{
    updateEnemies(dt, player);     // 1. Inimigos se movem, atacam e machucam o jogador
    updateProjectiles(dt, player); // 2. Projéteis se movem e acertam alvos (inimigos mortos são removidos aqui)
    checkCleared();                // 3. Se não sobrou ninguém, limpa a sala e destranca as portas
    updateLoot(player);            // 4. Se a sala está limpa, o jogador pode pegar o loot
}

// Inimigos: perseguem, atacam e causam dano ao encostar
void Room::updateEnemies(float dt, Player &player)
{
    Vector2 playerCenter = player.getCenter(); // Onde está o jogador (os inimigos mirão nesse ponto)
    Rectangle playerHitbox = player.getHitbox();

    for (Enemy &enemy : _enemies)
    {
        enemy.setTarget(playerCenter); // Informa o alvo (o update não recebe o jogador)
        enemy.update(dt, _collisionRects); // Persegue, sem atravessar paredes nem portas trancadas
        enemy.attack(_enemyProjectiles); // O inimigo comum não faz nada aqui, mas o gancho já está pronto

        if (CheckCollisionRecs(enemy.getHitbox(), playerHitbox)) // Encostou no jogador?
        {
            player.takeDamage(enemy.getContactDamage()); // A invulnerabilidade do jogador evita dano a cada frame
        }
    }

    for (MiniBoss &boss : _bosses)
    {
        if (boss.isDead())
        {
            continue; // Chefe morto não faz nada
        }

        boss.setTarget(playerCenter);
        boss.update(dt, _collisionRects);
        boss.attack(_enemyProjectiles); // A rajada de projéteis do chefe

        if (CheckCollisionRecs(boss.getHitbox(), playerHitbox))
        {
            player.takeDamage(boss.getContactDamage());
        }
    }
}

// Projéteis: movem, acertam alvos e os mortos são removidos
void Room::updateProjectiles(float dt, Player &player)
{
    // Projéteis do jogador: acertam inimigos
    for (Projectile &projectile : _playerProjectiles)
    {
        projectile.update(dt, _collisionRects); // Anda e morre na parede
        if (!projectile.isAlive())
        {
            continue; // Já morreu (parede ou tempo), não precisa testar acertos
        }

        for (Enemy &enemy : _enemies)
        {
            if (enemy.isDead())
            {
                continue; // Já foi morto por outro projétil neste frame
            }
            if (CheckCollisionRecs(projectile.getHitbox(), enemy.getHitbox()))
            {
                enemy.takeDamage(projectile.getDamage()); // Causa o dano
                projectile.destroy(); // O projétil some ao acertar
                break; // Um projétil acerta só um alvo
            }
        }

        if (!projectile.isAlive())
        {
            continue; // Já acertou um inimigo comum, não testa o chefe
        }

        for (MiniBoss &boss : _bosses)
        {
            if (boss.isDead())
            {
                continue;
            }
            if (CheckCollisionRecs(projectile.getHitbox(), boss.getHitbox()))
            {
                boss.takeDamage(projectile.getDamage());
                projectile.destroy();
                break;
            }
        }
    }

    // Projéteis dos inimigos: acertam o jogador
    for (Projectile &projectile : _enemyProjectiles)
    {
        projectile.update(dt, _collisionRects);
        if (!projectile.isAlive())
        {
            continue;
        }

        if (CheckCollisionRecs(projectile.getHitbox(), player.getHitbox()))
        {
            player.takeDamage(projectile.getDamage());
            projectile.destroy();
        }
    }

    // Remove os mortos. O laço vai de TRÁS PARA FRENTE para o erase não fazer o laço pular elementos
    for (int i = (int)_playerProjectiles.size() - 1; i >= 0; --i)
    {
        if (!_playerProjectiles[i].isAlive())
        {
            _playerProjectiles.erase(_playerProjectiles.begin() + i);
        }
    }

    for (int i = (int)_enemyProjectiles.size() - 1; i >= 0; --i)
    {
        if (!_enemyProjectiles[i].isAlive())
        {
            _enemyProjectiles.erase(_enemyProjectiles.begin() + i);
        }
    }

    // Os acertos acima podem ter matado inimigos comuns: remove-os (o chefe NUNCA é removido)
    for (int i = (int)_enemies.size() - 1; i >= 0; --i)
    {
        if (_enemies[i].isDead())
        {
            _enemies.erase(_enemies.begin() + i);
        }
    }
}

// Verifica se a sala foi limpa. Se foi: marca, destranca as portas e apaga os tiros inimigos que sobraram
void Room::checkCleared()
{
    if (_cleared)
    {
        return; // Já foi limpa antes (a sala não "respawna")
    }

    if (!_enemies.empty())
    {
        return; // Ainda há inimigos comuns vivos (os mortos já foram removidos)
    }

    for (const MiniBoss &boss : _bosses)
    {
        if (!boss.isDead())
        {
            return; // O chefe ainda está vivo
        }
    }

    _cleared = true; // Ninguém sobrou
    _enemyProjectiles.clear(); // Os tiros dos inimigos somem junto com eles

    for (Door &door : _doors)
    {
        door.unlock(); // Destranca todas as portas
    }
    rebuildCollisionRects(); // As portas destrancadas deixam de ser parede
}

// Loot: só pode ser pego com a sala limpa
void Room::updateLoot(Player &player)
{
    if (!_cleared)
    {
        return; // O loot só aparece depois de limpar a sala
    }

    Rectangle playerHitbox = player.getHitbox();

    for (Pickup &loot : _loot)
    {
        if (CheckCollisionRecs(loot.getHitbox(), playerHitbox)) // O jogador encostou no item?
        {
            loot.tryCollect(player); // Usa a poção. Com a vida cheia ela NÃO é usada e o item fica no lugar
        }
    }

    // Remove os itens já coletados (de trás para frente, pelo mesmo motivo dos projéteis)
    for (int i = (int)_loot.size() - 1; i >= 0; --i)
    {
        if (_loot[i].isCollected())
        {
            _loot.erase(_loot.begin() + i);
        }
    }
}

// Desenha a sala, de trás para frente (o que vem depois fica por cima)
void Room::draw() const
{
    _tilemap.draw(); // Chão e paredes

    for (const Door &door : _doors)
    {
        door.draw();
    }

    if (_cleared) // O loot só existe depois de limpar a sala
    {
        for (const Pickup &loot : _loot)
        {
            loot.draw();
        }
    }

    for (const Enemy &enemy : _enemies)
    {
        enemy.draw();
    }

    for (const MiniBoss &boss : _bosses)
    {
        if (!boss.isDead()) // Chefe morto não é desenhado (mas continua no vetor)
        {
            boss.draw();
        }
    }

    for (const Projectile &projectile : _playerProjectiles)
    {
        projectile.draw();
    }

    for (const Projectile &projectile : _enemyProjectiles)
    {
        projectile.draw();
    }
}

// Apaga todos os projéteis (o World chama ao sair da sala)
void Room::clearProjectiles()
{
    _playerProjectiles.clear();
    _enemyProjectiles.clear();
}

// Refaz a lista de colisão: paredes do mapa + portas que estão trancadas
void Room::rebuildCollisionRects()
{
    _collisionRects = _tilemap.getWallRects(); // Começa com uma cópia das paredes do mapa

    for (const Door &door : _doors)
    {
        if (door.isLocked())
        {
            _collisionRects.push_back(door.getArea()); // Porta trancada bloqueia como uma parede
        }
    }
}

const std::vector<Rectangle> &Room::getCollisionRects() const
{
    return _collisionRects;
}

std::vector<Projectile> &Room::getPlayerProjectiles()
{
    return _playerProjectiles;
}

// Devolve a porta que o hitbox está tocando (e que está destrancada), ou nullptr se nenhuma
const Door *Room::getDoorTouching(const Rectangle &playerHitbox) const
{
    for (const Door &door : _doors)
    {
        if (door.isTouching(playerHitbox))
        {
            return &door; // O & devolve o ENDEREÇO da porta dentro do vetor
        }
    }
    return nullptr;
}

Vector2 Room::getPlayerSpawn() const
{
    return _playerSpawn;
}

int Room::getPixelWidth() const
{
    return _tilemap.getPixelWidth();
}

int Room::getPixelHeight() const
{
    return _tilemap.getPixelHeight();
}

bool Room::isCleared() const
{
    return _cleared;
}

// O chefe foi derrotado? (só é verdade se a sala TEM um chefe e todos estão mortos)
bool Room::isBossDefeated() const
{
    if (_bosses.empty())
    {
        return false; // Esta sala não tem chefe
    }

    for (const MiniBoss &boss : _bosses)
    {
        if (!boss.isDead())
        {
            return false;
        }
    }
    return true;
}
