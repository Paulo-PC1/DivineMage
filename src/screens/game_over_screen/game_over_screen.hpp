#pragma once
#include "screens/screen/screen.hpp"
#include "raylib.h"

class GameOverScreen : public Screen {
public:
    GameOverScreen();

    ScreenType update(float dt) override;  // Tentar de novo → GAMEPLAY, Menu → MAIN_MENU
    void draw() override;

private:
    Rectangle _retryButton;
    Rectangle _menuButton;
};