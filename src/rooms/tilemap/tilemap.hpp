// DivineMage - Shooter/src/rooms/tilemap/tilemap.hpp
#pragma once // Diretiva de pré-processador para evitar múltiplas inclusões do mesmo arquivo  
#include <vector>
#include "raylib.h"
#include <string>
 

// Classe Tilemap representa um mapa de tiles (blocos) em um jogo, permitindo a manipulação e renderização de tiles em uma grade.
class TileMap {
  
public:
    
    // Construtor da classe 
    TileMap();
    
    // Destrutor da classe
    ~TileMap() = default;
    
    TileMap(const TileMap &) = delete;
    
    TileMap &operator=(const TileMap &) = delete;
    
    // Método para carregar as texturas do jogo (Lê json e textura e devolve true ou false)
    bool load(const std::string &jsonPath, const std::string &tilesetPath);
    
    // Método para descarregar as texturas (chama GameScreen)
    void unload();
    
    // Método para desenhar o mapa (tileset) na tela (_ground e depois _walls)
    void draw() const;
    
    // Método para pegar(devolver) os rects para colisão
    const std::vector<Rectangle> &getWallRects() const;
    
    // Método para devolver tamanho da sala em pixels
    int getPixelWidth() const;
    int getPixelHeight() const;
    
private:

    int _width;    // Largura da sala EM TILES (20)
    int _height;   // Altura da sala EM TILES (12)
    int _tileSize; // Tamanho de CADA tile em pixels (32), lido do JSON
    int _firstGid; // Usado para achar o tile no Png (vem de tilesets)
    int _columns; // Usado para achar o tile no Png (vem de tilesets)
    std::vector<int> _ground; // Contém os gids da camada do chao
    std::vector<int> _walls; // Contém os gids da camada da parede
    std::vector<Rectangle> _wallRects; // Contém um retângulo por tile de parede (para colisão)
    Texture2D _tileset; // Contém a textura do mapa (dungeon_tiles.png)
    
};