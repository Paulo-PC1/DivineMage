#include "player.hpp"

// Cria o jogador com posição inicial, velocidade, olhnado esquerda(falso) e se movendo(falso)
Player::Player(float x, float y, float speed) :
    _x(x), _y(y), _speed(speed), _facingLeft(false), _isMoving(false),
    _idleTexture(loadTexture("../../assets/sprites/Player.png", false)), // Carrega a textura do jogador parado
    _walkTexture(loadTexture("../../assets/sprites/player_walking.png", false)), // Carrega a textura do jogador se movendo
    _idleAnim(_idleTexture, 6, 0.2f),   // ajuste 6 pro total de frames real do seu novo Player.png
    _walkAnim(_walkTexture, 6, 0.15f)   // ajuste 8 pro total de frames real do player_walking.png
{}


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
    _isMoving = false;
    
    // Se a tecla W estiver pressionada, o jogador se move para cima
    if(IsKeyDown(KEY_W)) { 
        _y -= _speed * dt; 
        _isMoving = true;
    }
    // Se a tecla S estiver pressionada, o jogador se move para baixo
    if(IsKeyDown(KEY_S)) {
        _y += _speed * dt;
        _isMoving = true; // se esta se movendo variavel fica veradadeira mudando o sprite
    }
    // Se a tecla A estiver pressionada, o jogador se move para esquerda
    if(IsKeyDown(KEY_A)){
        _x -= _speed * dt;
        _isMoving = true;
        _facingLeft = true; // se moveu para esquerda vaviavel para inverter se torna verdadeira
    }
    // Se a tecla D estiver pressionada, o jogador se move para direita
    if(IsKeyDown(KEY_D)) { 
        _x += _speed * dt; // Se a tecla D estiver pressionada, o jogador se move para direita
         _isMoving = true;
        _facingLeft = false; // se moveu para direita vaviavel para inverter se torna falsa
    }
    
    if(_isMoving) {
        _walkAnim.update(dt); // Atualiza a animação do jogador andando
    } else {
        _idleAnim.update(dt); // Atualiza a animação do jogador parado
    }
}

// Desenha o jogador na tela
void Player::draw() const
{
    const Animation &anim = _isMoving ? _walkAnim : _idleAnim; // Se animação atual for igual a se mover carrega a walkAnim se não a IdleAnim
    Texture2D currentTexture = _isMoving ? _walkTexture : _idleTexture; // Se textura atual for igual a se mover carrega a walkTexture se não a IdleTexture
    
    Rectangle sourceRec = anim.getFrameRec();
    if (_facingLeft){
        sourceRec.width = -sourceRec.width; // espelha na hora do desenho, sem uso de textura extra
    }
    
    DrawTextureRec(currentTexture, sourceRec, Vector2{ _x, _y}, WHITE);
    
}
 
// Descarrega a textura do jogador
void Player::unload()
{
    UnloadTexture(_idleTexture); // Descarrega a textura do jogador parado da memoria
    UnloadTexture(_walkTexture); // Descarrega a textura do jogador andando da memoria

}

// Getters
float Player::getX() const { 
    return _x;  
}

float Player::getY() const
{
    return _y;
}
