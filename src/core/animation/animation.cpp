#include "animation.hpp"

// Cria a animação dividindo a textura pelo numero de sprites que ela possui
Animation::Animation(const Texture2D &texture, int totalFrames, float updateTime) :
    _totalFrames(totalFrames), _updateTime(updateTime)
{
    _frameWidth = texture.width / totalFrames; // Largura de cada frame
    _frameHeigth = texture.height; // Altura de cada frame (altura total da imagem)
    _frameRec = { 0.0f, 0.0f, (float)_frameWidth, (float)_frameHeigth }; // Retangulo para definir qual parte ira cortar da imagem
    _currentFrame = 0; // Frame atual
    _frameTime = 0.0f; // Tempo de atualização do frame
}

// Atualiza o frame atual se o tempo de atualização do frame for maior ou igual ao tempo definido
void Animation::update(float dt)
{
    _frameTime += dt; // Acumula o tempo de atualização do frame
 
    while (_frameTime >= _updateTime){
        _frameTime -= _updateTime; // Reseta o tempo de atualização do frame
        _currentFrame++; // Incrementa o frame atual
        if (_currentFrame >= _totalFrames){ // Se o frame atual for maior ou igual ao numero total de frames, reseta o frame atual
            _currentFrame = 0; // Reseta o frame atual
        }
        _frameRec.x = _currentFrame * _frameWidth; // Atualiza a posição do retangulo para cortar a imagem
    }
}
Rectangle Animation::getFrameRec() const
{
    return _frameRec;
}