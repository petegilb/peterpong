#include "peterpong.h"

PongGame::PongGame(){
    Player1 = std::make_unique<Player>();
    Player2 = std::make_unique<Player>();
}

void PongGame::StartGame(){
    if (Player1){
        Player1->BeginPlay();
    }
    if (Player2){
        Player2->BeginPlay();
    }
}

void PongGame::GameTick(){
    float DeltaTime = GetFrameTime();
}

void PongGame::RenderTick(){
    BeginDrawing();

    ClearBackground(SMOKYROSE);

    DrawText("Peter Pong.", 190, 200, 20, JASMINE);
    float width = GetScreenWidth()/2.0f, height = GetScreenHeight()/6.0f;
    Rectangle rec = {
        GetScreenWidth()/2.0f - width/2,
        GetScreenHeight()/2.0f - 5*(height/2),
        width, height
    };
    DrawRectangleRounded(rec, .8f, 36, JASMINE);

    EndDrawing();
}
