#pragma once
#include "raylib.h"

struct Animation {
    int totalFrames; // Número total de frames da animação
    int frameWidth; // Largura de cada frame
    int frameHeigth; // Altura de cada frame (altura total da imagem)
    Rectangle frameRec; // Retangulo para definir qual parte ira cortar da imagem
    int currentFrame; // Frame atual
    float frameTime; // Tempo de atualização do frame
    float updateTime; // Tempo de atualização dos frames
};

Animation initAnimation(const Texture2D &texture, int totalFrames, float updateTime);
void updateAnimation(Animation &anim, float dt);

