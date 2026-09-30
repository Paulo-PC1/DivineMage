#include "player.hpp"

// Cria o jogador com posição inicial, velocidade e textura inicial
Player::Player(float x, float y, float speed) :
    _x(x), _y(y), _oldPos({x, y}), _speed(speed)
{
    _texture = loadTexture("../../assets/sprites/Player.png", false); // Carrega a textura do jogador
}


// Carrega a textura do jogador, redimensiona e inverte a imagem se necessário
Texture2D Player::loadTexture(const char *filePath, bool flipHorizontal){
    
    Image img = LoadImage(filePath); // Carrega a imagem do jogador
    int newWidth = static_cast<int>(img.width * 3); // Aumenta a largura da imagem em 3 vezes
    int newHeigth = static_cast<int>(img.height * 3); // Aumenta a altura da imagem em 3 vezes
    if(flipHorizontal){
        ImageFlipHorizontal(&img); // Inverte a imagem horizontalmente para que o jogador ande para esquerda
    }
    ImageResizeNN(&img, newWidth, newHeigth); // Redimensiona a imagem do jogador
    Texture2D texture = LoadTextureFromImage(img); // Carrega a textura do jogador
    UnloadImage(img); // Descarrega a imagem do jogador da memoria
    return texture; // Retorna a textura do jogador
}

// Atualiza o movimento e a textura do jogador
void Player::update(float dt)
{
    if(IsKeyDown(KEY_W)) _y -= _speed * dt; // Se a tecla W estiver pressionada, o jogador se move para cima
    if(IsKeyDown(KEY_S)) _y += _speed * dt; // Se a tecla S estiver pressionada, o jogador se move para baixo
    if(IsKeyDown(KEY_A)){ // Se a tecla A estiver pressionada, o jogador se move para esquerda
        _x -= _speed * dt; // Se a tecla A estiver pressionada, o jogador se move para esquerda
        UnloadTexture(_texture); // Descarrega a textura do jogador
        _texture = loadTexture("../../assets/sprites/player_walking.png", true); // Carrega a imagem do jogador andando para esquerda (invertida)
    }
    if(IsKeyDown(KEY_D)) { // Se a tecla D estiver pressionada, o jogador se move para direita
        _x += _speed * dt; // Se a tecla D estiver pressionada, o jogador se move para direita
        UnloadTexture(_texture); // Descarrega a textura do jogador
        _texture = loadTexture("../../assets/sprites/player_walking.png", false); // Carrega a imagem do jogador andando
    }
    if(_oldPos.x == _x && _oldPos.y == _y){ // Se a posição do jogador não mudou, significa que ele parou de se mover
        UnloadTexture(_texture); // Descarrega a textura do jogador
        _texture = loadTexture("../../assets/sprites/Player.png", false); // Carrega a imagem do jogador
    }
 
    _oldPos = {_x, _y }; // Atualiza a posição antiga do jogador
}

// Desenha o jogador na tela
void Player::draw(const Animation &anim) const
{
    DrawTextureRec(_texture, anim.getFrameRec(), Vector2{ _x, _y }, WHITE); // Desenha a textura do jogador na posição
}
 
// Descarrega a textura do jogador
void Player::unload()
{
    UnloadTexture(_texture); // Descarrega a textura do jogador da memoria
}

// Getters
float Player::getX() const { 
    return _x;  
}

float Player::getY() const
{
    return _y;
}

Texture2D Player::getTexture() const
{
    return _texture;
}