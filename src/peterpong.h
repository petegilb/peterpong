#pragma once
#include <memory>

#include "raylib.h"
#include "player.h"

// https://coolors.co/795c5f-a69658-d9b26f-fadf7f-f2e29f
constexpr Color SMOKYROSE{ 121, 92, 95, 255 };
constexpr Color JASMINE{250, 223, 127, 255};
constexpr int screenWidth = 800;
constexpr int screenHeight = 450;

class PongGame{
public:
    PongGame();

    void StartGame();

    void GameTick();

    void RenderTick();
private:
    // There's always two players.
    std::unique_ptr<Player> Player1;
    std::unique_ptr<Player> Player2;
};
