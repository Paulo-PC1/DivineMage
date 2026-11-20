#pragma once
#include "raylib.h"

// Toca UMA música em loop. Cada tela cria a sua (ou mais de uma, como a GameScreen)
class MusicPlayer {
public:

    MusicPlayer();
    
    ~MusicPlayer();
    MusicPlayer(const MusicPlayer &) = delete;            // Music não deve ser copiada
    MusicPlayer &operator=(const MusicPlayer &) = delete;

    bool load(const char *filePath); // false se o arquivo não existir (o jogo continua, só sem som)
    void play();
    void stop();
    void update();                   // PRECISA ser chamado todo frame, senão a música engasga e para
    void setVolume(float volume);    // 0.0f a 1.0f
    void unload();

private:
    Music _music;
    bool _loaded;
};