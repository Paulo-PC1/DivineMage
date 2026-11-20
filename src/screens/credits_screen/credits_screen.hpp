#pragma once
#include "screens/screen/screen.hpp"
#include "core/audio/music_player.hpp"
#include "raylib.h"

class CreditsScreen : public Screen {
public:
    CreditsScreen();

    ScreenType update(float dt) override;  // botão Voltar ou ESC → MAIN_MENU
    void draw() override;

private:
    Rectangle _backButton;
    MusicPlayer _music;
};