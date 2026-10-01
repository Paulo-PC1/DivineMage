#include "player.hpp"
#include "raymath.h"
#include <algorithm> // Para std::min

// Construtor, cria o jogador com posição inicial, velocidade e textura inicial
Player::Player(float x, float y, float speed) :
    _x(x), _y(y), _speed(speed),
     _facingLeft(false), _isMoving(false),
    _idleTexture(loadTexture(ASSETS_PATH "sprites/Player.png")), // Carrega a textura do jogador parado
    _walkTexture(loadTexture(ASSETS_PATH "sprites/player_walking.png")), // Carrega a textura do jogador andando
    _idleAnim(_idleTexture, 6, 0.2f),   // ajuste 6 pro total de frames real do seu novo Player.png
    _walkAnim(_walkTexture, 6, 0.15f)   // ajuste 6 pro total de frames real do player_walking.png
{}


// Carrega a textura do jogador, redimensiona e inverte a imagem se necessário
Texture2D Player::loadTexture(const char *filePath){
    
    Texture2D texture = LoadTexture(filePath); // Carrega a textura do jogador
    SetTextureFilter(texture, TEXTURE_FILTER_POINT); // Define o filtro de textura para ponto, garantindo que a textura seja renderizada com pixels nítidos, sem suavização
    return texture; // Retorna a textura carregada
}

// Atualiza o movimento e a textura do jogador
void Player::update(float dt) {
    dt = std::min(dt, 0.05f);  // Limita o delta time para evitar movimentos muito rápidos em caso de quedas de FPS
    _isMoving = false; // Reseta a variável de movimento para falso no início da atualização

    // Calcula a direção do movimento com base nas teclas pressionadas
    Vector2 direction = { 0.0f, 0.0f };
    if (IsKeyDown(KEY_W)) direction.y -= 1.0f; // Se a tecla W estiver pressionada, move o jogador para cima (diminuindo a coordenada y)
    if (IsKeyDown(KEY_S)) direction.y += 1.0f; // Se a tecla S estiver pressionada, move o jogador para baixo (aumentando a coordenada y)
    if (IsKeyDown(KEY_A)) direction.x -= 1.0f; // Se a tecla A estiver pressionada, move o jogador para a esquerda (diminuindo a coordenada x)
    if (IsKeyDown(KEY_D)) direction.x += 1.0f; // Se a tecla D estiver pressionada, move o jogador para a direita (aumentando a coordenada x)
 
    // Normaliza a direção do movimento para garantir que a velocidade seja consistente em todas as direções
    if (Vector2Length(direction) > 0) {
        direction = Vector2Normalize(direction); // Normaliza o vetor de direção para que sua magnitude seja 1, garantindo movimento uniforme em todas as direções
        _x += direction.x * _speed * dt; // Atualiza a posição do jogador no eixo x com base na direção, velocidade e delta time
        _y += direction.y * _speed * dt; // Atualiza a posição do jogador no eixo y com base na direção, velocidade e delta time
        _isMoving = true; // Atualiza a variável de movimento para verdadeiro, indicando que o jogador está se movendo
        
        // Atualiza a direção que o jogador está olhando com base na direção do movimento
        if (direction.x != 0) _facingLeft = (direction.x < 0);
    }
    
    // Atualiza a animação do jogador com base no estado de movimento
    static bool wasMoving = false;
    if (_isMoving && !wasMoving) { // Se o jogador começou a se mover, reseta a animação de caminhada
        _walkAnim.reset(); // Reseta a animação do jogador andando para o frame inicial
    }
    if (!_isMoving && wasMoving){  // Se o jogador parou de se mover, reseta a animação de parada
        _idleAnim.reset(); // Reseta a animação do jogador parado para o frame inicial
    }
    wasMoving = _isMoving; // Atualiza o estado de movimento anterior para a próxima atualização
    
    // Atualiza a animação do jogador com base no estado de movimento
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
    
    // Obtém o retângulo da animação atual para desenhar a parte correta da textura
    Rectangle sourceRec = anim.getFrameRec();
    if (_facingLeft){
        sourceRec.width = -sourceRec.width; // espelha na hora do desenho, sem uso de textura extra
    }
    // Desenha a textura do jogador na tela usando o retângulo da animação atual e a posição do jogador
    DrawTextureRec(currentTexture, sourceRec, Vector2{ _x, _y}, WHITE);
    
}
 
// Descarrega a textura do jogador
void Player::unload()
{
    UnloadTexture(_idleTexture); // Descarrega a textura do jogador parado da memoria
    UnloadTexture(_walkTexture); // Descarrega a textura do jogador andando da memoria

}

Vector2 Player::getCenter() const {
    // _idleTexture.width já reflete o x3 do redimensionamento
    return {
        _x + _idleTexture.width / 2.0f, 
        _y + _idleTexture.height / 2.0f
    };
}

// Getters
float Player::getX() const { 
    return _x;  
}

float Player::getY() const
{
    return _y;
}
