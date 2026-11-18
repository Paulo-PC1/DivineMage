//DivineMage - Shooter/src/entities/player/player.cpp
#include "entities/player/player.hpp" // Inclui o arquivo de cabeçalho da classe Player, que contém a declaração da classe e seus membros
#include "raymath.h" // Inclui a biblioteca Raymath para operações matemáticas, como normalização de vetores e cálculo de comprimento de vetores

//namespace para constantes do jogador
namespace {
    constexpr float HITBOX_OFFSET_X = 9.0f;
    constexpr float HITBOX_OFFSET_Y = 16.0f;
    constexpr float HITBOX_WIDTH    = 14.0f;
    constexpr float HITBOX_HEIGHT   = 16.0f;
    constexpr int   MAX_HEALTH      = 100; 
    constexpr float INVULNERABILITY_DURATION = 0.5f; // Duração da invulnerabilidade em segundos
}

// Construtor, cria o jogador com posição inicial, velocidade e textura inicial
Player::Player(float x, float y, float speed) :
    Actor(x, y, HITBOX_OFFSET_X, HITBOX_OFFSET_Y, HITBOX_WIDTH, HITBOX_HEIGHT, speed, MAX_HEALTH), // Inicializa a posição e velocidade do jogador com os valores fornecidos
    _facingLeft(false), _isMoving(false), _wasMoving(false), // Inicializa as variáveis de direção e movimento do jogador como falso
    _idleTexture(loadTexture(ASSETS_PATH "sprites/player/Magu.png")), // Carrega a textura do jogador parado
    _walkTexture(loadTexture(ASSETS_PATH "sprites/player/Magu_Walk.png")), // Carrega a textura do jogador andando
    _idleAnim(_idleTexture, 6, 0.2f),   // ajuste 6 pro total de frames real do seu novo Player.png
    _walkAnim(_walkTexture, 6, 0.15f)   // ajuste 6 pro total de frames real do player_walking.png
    // _staff não aparece: usa o construtor padrão do Staff
{
    // _invulnerabilityDuration é membro da BASE, e a lista de inicialização só inicia membros da própria classe.
    // Por isso ele é ajustado aqui, no corpo do construtor (o Actor o iniciou com 0)
    _invulnerabilityDuration = INVULNERABILITY_DURATION;
}


// Carrega a textura do jogador, redimensiona e inverte a imagem se necessário
Texture2D Player::loadTexture(const char *filePath)
{
    
    Texture2D texture = LoadTexture(filePath); // Carrega a textura do jogador
    SetTextureFilter(texture, TEXTURE_FILTER_POINT); // Define o filtro de textura para ponto, garantindo que a textura seja renderizada com pixels nítidos, sem suavização
    return texture; // Retorna a textura carregada
}

// Atualiza o movimento, colisão e a textura do jogador
void Player::update(float dt, const std::vector<Rectangle> &walls) 
{
    _isMoving = false; // Reseta a variável de movimento para falso no início da atualização

    // Calcula a direção do movimento com base nas teclas pressionadas
    Vector2 direction = { 0.0f, 0.0f };
    if (IsKeyDown(KEY_W)) 
    {
        direction.y -= 1.0f; // Se a tecla W estiver pressionada, move o jogador para cima (diminuindo a coordenada y)
    } 
    if (IsKeyDown(KEY_S)) 
    {
        direction.y += 1.0f ;
    }
    if (IsKeyDown(KEY_A)) 
    {
        direction.x -= 1.0f; // Se a tecla A estiver pressionada, move o jogador para a esquerda (diminuindo a coordenada x)   
    }
    if (IsKeyDown(KEY_D)) 
    {
        direction.x += 1.0f; // Se a tecla D estiver pressionada, move o jogador para a direita (aumentando a coordenada x)
    } 
 
    // Normaliza a direção do movimento para garantir que a velocidade seja consistente em todas as direções
    if (Vector2Length(direction) > 0) 
    {
        direction = Vector2Normalize(direction); // Normaliza o vetor de direção para que sua magnitude seja 1, garantindo movimento uniforme em todas as direções
        Vector2 displacement = Vector2Scale(direction, _speed * dt); // Calcula o deslocamento do jogador multiplicando a direção normalizada pela velocidade e pelo delta time (dt)
        moveWithCollision(displacement, walls); // Move o jogador com colisão, verificando se há paredes no caminho e ajustando a posição do jogador conforme necessário
        
        // Atualiza o estado de movimento e a direção do jogador com base na direção do movimento
        _isMoving = true;
        if (direction.x != 0) _facingLeft = (direction.x < 0); // 
    }
    
    if (_isMoving && !_wasMoving) // Se o jogador começou a se mover, reseta a animação de caminhada
    { 
        _walkAnim.reset(); // Reseta a animação do jogador andando para o frame inicial
    }
    if (!_isMoving && _wasMoving) // Se o jogador parou de se mover, reseta a animação de parada
    {  
        _idleAnim.reset(); // Reseta a animação do jogador parado para o frame inicial
    }
    _wasMoving = _isMoving; // Atualiza o estado de movimento anterior para a próxima atualização
    
    // Atualiza a animação do jogador com base no estado de movimento
    if(_isMoving) 
    {
        _walkAnim.update(dt); // Atualiza a animação do jogador andando
    }else 
    {
        _idleAnim.update(dt); // Atualiza a animação do jogador parado
    }
    
    updateInvulnerability(dt); // Desconta o tempo da invulnerabilidade (método do Actor)
    _staff.update(dt);         // [ARMA] Desconta o cooldown do cajado
}

// Desenha o jogador na tela
void Player::draw() const
{
    // Opcional: pisca enquanto está invulnerável (apague estas 4 linhas se não quiser o efeito)
    if (isInvulnerable() && (int)(GetTime() * 10.0) % 2 == 0)
    {
        return; // não desenha neste instante, o que cria o piscar
    }
    
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

// [ARMA] Atira o cajado na direção do ponto de mira (em coordenadas do mundo)
void Player::shoot(Vector2 aimWorldPosition, std::vector<Projectile> &projectiles)
{
    if (!_staff.canShoot())
    {
        return; // ainda em cooldown
    }

    Vector2 origin = getCenter(); // de onde o tiro sai (centro do hitbox, vindo do Entity)
    Vector2 direction = Vector2Subtract(aimWorldPosition, origin);

    if (Vector2Length(direction) < 0.001f)
    {
        return; // mouse exatamente no centro: não existe direção para normalizar
    }

    direction = Vector2Normalize(direction);
    _staff.shoot(origin, direction, projectiles);
}
 
// Descarrega a textura do jogador
void Player::unload() 
{
    UnloadTexture(_idleTexture); // Descarrega a textura do jogador parado da memoria
    UnloadTexture(_walkTexture); // Descarrega a textura do jogador andando da memoria

}
