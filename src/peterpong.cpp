#include "peterpong.h"

PongGame::PongGame(){
    Player1 = std::make_unique<Player>();
    Player2 = std::make_unique<Player>();
    Player2->bIsPlayer1 = false;
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
    // if (IsKeyPressed(KEY_F)) ToggleBorderlessWindowed();
    // if (IsKeyPressed(KEY_R))
    // {
    //     if (IsWindowState(FLAG_WINDOW_RESIZABLE)) ClearWindowState(FLAG_WINDOW_RESIZABLE);
    //     else SetWindowState(FLAG_WINDOW_RESIZABLE);
    // }
}

void PongGame::RenderTick(){
    BeginDrawing();

    ClearBackground(SLIMY_BLUE);

    DrawRectangle(0, 0, screenWidth, 16, SLIMY_GREEN_M);
    DrawRectangle(0, screenHeight-16, screenWidth, 16, SLIMY_GREEN_M);

    // Middle rectangle
    constexpr int numLines = 16;
    constexpr int lineGap = 16;
    constexpr int lineWidth = 14;
    for (int i = 0; i < numLines; i++){
        DrawRectangle(screenWidth/2 - lineWidth/2, screenHeight/numLines * i, lineWidth, screenHeight/numLines - lineGap, SLIMY_GREEN_M);
    }

    DrawText("0", screenWidth/2.0f - ScoreOffset.x - 16, ScoreOffset.y, 72, SLIMY_YELLOW);
    DrawText("0", screenWidth/2.0f + ScoreOffset.x - 16, ScoreOffset.y, 72, SLIMY_YELLOW);

    if (Player1){
        Player1->Draw();
    }
    if (Player2){
        Player2->Draw();
    }

    EndDrawing();
}
