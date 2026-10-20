// DivineMage - Shooter/src/rooms/tilemap/tilemap.cpp
#include <fstream>
#include "nlohmann/json.hpp"
#include <vector>
#include "rooms/tilemap/tilemap.hpp" 

using json = nlohmann::json;

TileMap::TileMap() : _width(0), _height(0), _tileSize(0), _firstGid(0), _columns(0), _tileset{}
{
    
}

bool TileMap::load(const std::string &jsonPath, const std::string &tilesetPath)
{
    
    _ground.clear();
    _walls.clear();
    _wallRects.clear();
    
    std::ifstream file(jsonPath);
    if (!file)
    {
        TraceLog(LOG_ERROR, "TileMap: nao abriu o arquivo %s", jsonPath.c_str());
        return false;
    }
    
    try
    {
        json j = json::parse(file);
        
        _width = j["width"];
        _height = j["height"];
        _tileSize = j["tilewidth"];
        _firstGid = j["tilesets"][0]["firstgid"];
        _columns = j["tilesets"][0]["columns"];
        
        for(auto &layer : j["layers"])
        {
            if(layer["type"] != "tilelayer")
            {
                continue;
            }
            auto data = layer["data"].get<std::vector<int>>();
            if(layer["name"] == "walls")
            {
                _walls = data;
            }
            else if(layer["name"] == "ground")
            {
                _ground = data;
            }
        }
    }
    catch(const json::exception &e)
    {
        TraceLog(LOG_ERROR, "TileMap: erro ao ler o JSON %s: %s", jsonPath.c_str(), e.what());
        return false;
    }
    
    if((int)_walls.size() != _width * _height)
    {
        TraceLog(LOG_ERROR, "TileMap: camada walls tem %d tiles, esperado %d", (int)_walls.size(), _width * _height);
        return false;
    }

if((int)_ground.size() != _width * _height)
    {
        TraceLog(LOG_ERROR, "TileMap: camada ground tem %d tiles, esperado %d", (int)_ground.size(), _width * _height);
        return false;
    }
    
    for(int i = 0; i < (int)_walls.size(); ++i)
    {
        if(_walls[i] == 0)
        {
            continue;
        }
        _wallRects.push_back({ (float)((i % _width) *_tileSize), (float)((i / _width) *_tileSize), (float)_tileSize, (float)_tileSize});
    
    }
    
    unload(); // Descarrega a textura antiga, se existir, antes de carregar a nova

    _tileset = LoadTexture(tilesetPath.c_str());
    if(_tileset.id == 0)
    {
        TraceLog(LOG_ERROR, "TileMap: nao carregou a textura %s", tilesetPath.c_str());
        return false;
    }

    return true;
}

void TileMap::unload()
{
    if(_tileset.id != 0) // Só descarrega se houver textura carregada
    {
        UnloadTexture(_tileset);
        _tileset = {}; // Zera, para uma segunda chamada não fazer nada
    } 
}

const std::vector<Rectangle> &TileMap::getWallRects() const
{
    return _wallRects;
}
    
void TileMap::draw() const
{
    // As duas camadas, na ordem de desenho: chão primeiro, paredes por cima
    const std::vector<int> *layers[2] = { &_ground, &_walls };

    for(int l = 0; l < 2; ++l)
    {
        const std::vector<int> &layer = *layers[l];

        for(int i = 0; i < (int)layer.size(); ++i)
        {
            if(layer[i] == 0) // 0 = célula vazia
            {
                continue;
            }

            int index = layer[i] - _firstGid; // Posição do tile no PNG

            // Recorte do tile dentro do PNG
            Rectangle source = {
                (float)((index % _columns) * _tileSize),
                (float)((index / _columns) * _tileSize),
                (float)_tileSize,
                (float)_tileSize
            };

            // Posição da célula no mundo
            Vector2 position = {
                (float)((i % _width) * _tileSize),
                (float)((i / _width) * _tileSize)
            };

            DrawTextureRec(_tileset, source, position, WHITE);
        }
    }
}

int TileMap::getPixelWidth() const
{
    return _width * _tileSize;
}
int TileMap::getPixelHeight() const
{
    return _height * _tileSize;
}