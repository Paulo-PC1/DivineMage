// DivineMage - Shooter/src/rooms/tilemap/tilemap.cpp
#include <fstream> // Inclui a biblioteca fstream para abrir e ler o arquivo JSON do mapa (std::ifstream)
#include "nlohmann/json.hpp" // Inclui a biblioteca nlohmann/json para interpretar (parsear) o JSON exportado pelo Tiled
#include <vector> // Inclui a biblioteca vector para guardar as camadas (gids) e os retângulos de colisão
#include "rooms/tilemap/tilemap.hpp" // Inclui a classe TileMap, que contém a declaração dos métodos e membros implementados aqui

using json = nlohmann::json; // Cria um apelido curto para o tipo json da biblioteca nlohmann

// Construtor, zera todos os atributos para a classe começar em um estado válido (mapa vazio, sem textura)
TileMap::TileMap() : _width(0), _height(0), _tileSize(0), _firstGid(0), _columns(0), _tileset{} // _tileset{} zera a textura (id = 0), indicando que nenhuma textura foi carregada
{
    
}

// Carrega o mapa: lê o JSON (tamanho e camadas), monta os retângulos de colisão e carrega a textura do tileset
// Devolve true se tudo deu certo e false se qualquer etapa falhar (o motivo é registrado no log)
bool TileMap::load(const std::string &jsonPath, const std::string &tilesetPath)
{
    
    _ground.clear(); // Limpa a camada do chão de um mapa carregado anteriormente
    _walls.clear(); // Limpa a camada das paredes de um mapa carregado anteriormente
    _wallRects.clear(); // Limpa os retângulos de colisão de um mapa carregado anteriormente
    
    std::ifstream file(jsonPath); // Abre o arquivo JSON do mapa para leitura
    if (!file) // Se o arquivo não abriu (caminho errado, arquivo inexistente, etc.)
    {
        TraceLog(LOG_ERROR, "TileMap: nao abriu o arquivo %s", jsonPath.c_str()); // Registra o erro no log da Raylib
        return false; // Falha ao carregar o mapa
    }
    
    try // Qualquer erro de leitura do JSON (campo ausente, tipo errado, JSON inválido) cai no catch abaixo
    {
        json j = json::parse(file); // Lê o arquivo inteiro e transforma em um objeto json
        
        _width = j["width"]; // Largura do mapa EM TILES
        _height = j["height"]; // Altura do mapa EM TILES
        _tileSize = j["tilewidth"]; // Tamanho de cada tile em pixels (usa a largura, pois os tiles são quadrados)
        _firstGid = j["tilesets"][0]["firstgid"]; // Gid do primeiro tile do tileset (usado para achar o tile no PNG)
        _columns = j["tilesets"][0]["columns"]; // Quantidade de colunas de tiles no PNG do tileset (usado para achar o tile no PNG)
        
        for(auto &layer : j["layers"]) // Percorre todas as camadas do mapa
        {
            if(layer["type"] != "tilelayer") // Ignora camadas que não são de tiles (ex: camadas de objetos)
            {
                continue; // Pula para a próxima camada
            }
            auto data = layer["data"].get<std::vector<int>>(); // Converte o array "data" da camada em um vector de gids (um por célula)
            if(layer["name"] == "walls") // Se a camada se chama "walls"
            {
                _walls = data; // Guarda os gids da camada das paredes
            }
            else if(layer["name"] == "ground") // Se a camada se chama "ground"
            {
                _ground = data; // Guarda os gids da camada do chão
            }
        }
    }
    catch(const json::exception &e) // Captura erros da biblioteca json (parse, tipo errado, chave inexistente)
    {
        TraceLog(LOG_ERROR, "TileMap: erro ao ler o JSON %s: %s", jsonPath.c_str(), e.what()); // Registra o erro e a mensagem detalhada da biblioteca
        return false; // Falha ao carregar o mapa
    }
    
    // Validação: cada camada precisa ter exatamente uma célula por tile do mapa (largura x altura)
    if((int)_walls.size() != _width * _height) // Se a camada walls tem uma quantidade de tiles diferente da esperada
    {
        TraceLog(LOG_ERROR, "TileMap: camada walls tem %d tiles, esperado %d", (int)_walls.size(), _width * _height); // Registra o erro com o valor encontrado e o esperado
        return false; // Falha ao carregar o mapa
    }

if((int)_ground.size() != _width * _height) // Se a camada ground tem uma quantidade de tiles diferente da esperada
    {
        TraceLog(LOG_ERROR, "TileMap: camada ground tem %d tiles, esperado %d", (int)_ground.size(), _width * _height); // Registra o erro com o valor encontrado e o esperado
        return false; // Falha ao carregar o mapa
    }
    
    // Cria um retângulo de colisão para cada tile de parede
    for(int i = 0; i < (int)_walls.size(); ++i) // Percorre todas as células da camada de paredes
    {
        if(_walls[i] == 0) // 0 = célula vazia, não há parede aqui
        {
            continue; // Pula para a próxima célula
        }
        // i % _width = coluna e i / _width = linha da célula, multiplicando pelo tamanho do tile obtém a posição em pixels
        _wallRects.push_back({ (float)((i % _width) *_tileSize), (float)((i / _width) *_tileSize), (float)_tileSize, (float)_tileSize});
    
    }
    
    unload(); // Descarrega a textura antiga, se existir, antes de carregar a nova

    _tileset = LoadTexture(tilesetPath.c_str()); // Carrega a imagem do tileset (dungeon_tiles.png) para a GPU
    if(_tileset.id == 0) // Se o id da textura é 0, a Raylib não conseguiu carregar a imagem
    {
        TraceLog(LOG_ERROR, "TileMap: nao carregou a textura %s", tilesetPath.c_str()); // Registra o erro no log da Raylib
        return false; // Falha ao carregar o mapa
    }

    return true; // Mapa, colisões e textura carregados com sucesso
}

// Descarrega a textura do tileset da memória (chamado pelo GameScreen e também pelo load antes de carregar uma nova textura)
void TileMap::unload()
{
    if(_tileset.id != 0) // Só descarrega se houver textura carregada
    {
        UnloadTexture(_tileset); // Libera a textura da memória da GPU
        _tileset = {}; // Zera, para uma segunda chamada não fazer nada
    } 
}

// Getter que devolve os retângulos de colisão das paredes (por referência constante, evitando uma cópia do vector)
const std::vector<Rectangle> &TileMap::getWallRects() const
{
    return _wallRects; // Retorna um retângulo por tile de parede
}
    
// Desenha o mapa na tela, tile por tile (chão primeiro e paredes por cima)
void TileMap::draw() const
{
    // As duas camadas, na ordem de desenho: chão primeiro, paredes por cima
    const std::vector<int> *layers[2] = { &_ground, &_walls };

    for(int l = 0; l < 2; ++l) // Percorre as duas camadas na ordem do array
    {
        const std::vector<int> &layer = *layers[l]; // Referência para a camada atual (sem copiar o vector)

        for(int i = 0; i < (int)layer.size(); ++i) // Percorre todas as células da camada
        {
            if(layer[i] == 0) // 0 = célula vazia
            {
                continue; // Não há nada para desenhar, pula para a próxima célula
            }

            int index = layer[i] - _firstGid; // Posição do tile no PNG

            // Recorte do tile dentro do PNG
            Rectangle source = {
                (float)((index % _columns) * _tileSize), // Posição x no PNG: coluna do tile x tamanho do tile
                (float)((index / _columns) * _tileSize), // Posição y no PNG: linha do tile x tamanho do tile
                (float)_tileSize, // Largura do recorte (um tile)
                (float)_tileSize // Altura do recorte (um tile)
            };

            // Posição da célula no mundo
            Vector2 position = {
                (float)((i % _width) * _tileSize), // Posição x no mundo: coluna da célula x tamanho do tile
                (float)((i / _width) * _tileSize) // Posição y no mundo: linha da célula x tamanho do tile
            };

            DrawTextureRec(_tileset, source, position, WHITE); // Desenha o recorte do tileset na posição da célula (WHITE = sem alterar a cor)
        }
    }
}

// Getter que devolve a largura total da sala em pixels (largura em tiles x tamanho do tile)
int TileMap::getPixelWidth() const
{
    return _width * _tileSize; // Largura da sala em pixels
}
// Getter que devolve a altura total da sala em pixels (altura em tiles x tamanho do tile)
int TileMap::getPixelHeight() const
{
    return _height * _tileSize; // Altura da sala em pixels
}