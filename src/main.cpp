#include <iostream>
#include <memory>

#include "raylib.h"
#include "peterpong.h"

// Entry point for the program.
int main(){
    std::cout << "Starting peterpong..." << std::endl;

    InitWindow(screenWidth, screenHeight, "peter pong");
    InitAudioDevice();

    // Lock the max framerate at 60fps
    SetTargetFPS(60);

    // Create a new instance of the game.
    auto GameInstance = std::make_unique<PongGame>();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        GameInstance->GameTick();
        GameInstance->RenderTick();
    }

    // De-Initialization
    CloseAudioDevice();
    CloseWindow();
    std::cout << "Closing peterpong..." << std::endl;
    return 0;
}