#pragma once
#include "raylib.h"

class Animation {
    
    public:
        //Construtor, cria a animação dividindo a textura pelo número de frames
        explicit Animation(const Texture2D &texture, int totalFrames, float updateTime);
    
        //Atualiza o frame atual conforme o tempo passa
        void update(float dt);
        
        //Getter usado por quem for desenhar com essa animação (ex: Player::draw)
        Rectangle getFrameRec() const;
    
    private:
        int _totalFrames; // Número total de frames da animação
        int _frameWidth; // Largura de cada frame
        int _frameHeigth; // Altura de cada frame (altura total da imagem)
        Rectangle _frameRec; // Retangulo para definir qual parte ira cortar da imagem
        int _currentFrame; // Frame atual
        float _frameTime; // Tempo de atualização do frame
        float _updateTime; // Tempo de atualização dos frames
};


