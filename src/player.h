#pragma once
#include <string>

#include "raylib.h"

class Player{
public:
    Player();

    void BeginPlay();
    void Tick(float DeltaTime);

    Vector2 Position = Vector2{0.f, 0.f};

private:
    std::string name;
};
