#pragma once
#include "screens/screen/screen.hpp"
#include "core/audio/music_player.hpp"
#include "raylib.h"

class MenuScreen : public Screen {
public:
    MenuScreen();

    ScreenType update(float dt) override;  // clique em Jogar/Créditos/Sair devolve o destino
    void draw() override;

private:
    Rectangle _playButton;      // áreas clicáveis (CheckCollisionPointRec com o mouse)
    Rectangle _creditsButton;
    Rectangle _exitButton;
    MusicPlayer _music;
};