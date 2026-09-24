#include "animation.h"

// Cria a animação dividindo a textura pelo numero de sprites que ela possui
Animation initAnimation(const Texture2D &texture, int totalFrames, float updateTime)
{
    Animation anim;
    anim.totalFrames = totalFrames; // Numero total de frames
    anim.frameWidth = texture.width / totalFrames; // Largura de cada frame
    anim.frameHeigth = texture.height; // Altura de cada frame (altura total da imagem)
    anim.frameRec = { 0.0f, 0.0f, (float)anim.frameWidth, (float)anim.frameHeigth }; // Retangulo para definir qual parte ira cortar da imagem
    anim.currentFrame = 0; // Frame atual
    anim.frameTime = 0.0f; // Tempo de atualização do frame
    anim.updateTime = updateTime; // Tempo de atualização dos frames
    return anim;
}

// Atualiza o frame atual se o tempo de atualização do frame for maior ou igual ao tempo definido
void updateAnimation(Animation &anim, float dt)
{
    anim.frameTime += dt; // Acumula o tempo de atualização do frame
 
    if (anim.frameTime >= anim.updateTime){
        anim.frameTime -= anim.updateTime; // Reseta o tempo de atualização do frame
        anim.currentFrame++; // Incrementa o frame atual
        if (anim.currentFrame >= anim.totalFrames){ // Se o frame atual for maior ou igual ao numero total de frames, reseta o frame atual
            anim.currentFrame = 0; // Reseta o frame atual
        }
        anim.frameRec.x = anim.currentFrame * anim.frameWidth; // Atualiza a posição do retangulo para cortar a imagem
    }
}