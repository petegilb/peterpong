#pragma once
#include <string>

#include "raylib.h"

constexpr int PaddleWidth = 24;
constexpr int PaddleHeight = 96;
constexpr int PaddleXOffset = 32;

class Player{
public:
    Player();

    void BeginPlay();
    void Tick(float DeltaTime);
    void Draw();

    Vector2 Position = Vector2{0.f, 0.f};

    Texture2D PaddleTexture;

    bool bIsPlayer1 = true;
    bool bIsInitialized = false;

private:
    std::string name;
};
