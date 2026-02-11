#include "peterpong.h"

#include <iostream>

#include "ball.h"

PongGame::PongGame(){
    Player1 = std::make_unique<Player>();
    Player2 = std::make_unique<Player>();
    Player2->bIsPlayer1 = false;

    GameBall = std::make_unique<Ball>();
    GameBall->Player1 = Player1.get();
    GameBall->Player2 = Player2.get();


    GameBall->OnGoal = [this](bool bLeft)
    {
        HandleGoal(bLeft);
    };

    SetRoundTimer();
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
    if (Player1 && Player2){
        Player1->Tick(DeltaTime);
        Player2->Tick(DeltaTime);
    }
    if (GameBall && Player1 && Player2 && Player1->bIsInitialized && Player2->bIsInitialized){
        GameBall->Tick(DeltaTime);
    }

    // If there's a round timer, let's restart the game here
    if (RoundTimer > 0 && GetTime() > RoundTimer){
        if (GameBall){
            GameBall->Start();
        }
        RoundTimer = -1;
    }
}

void PongGame::RenderTick(){
    BeginDrawing();

    ClearBackground(SLIMY_BLUE);

    // Middle line
    constexpr int numLines = 16;
    constexpr int lineGap = 16;
    constexpr int lineWidth = 14;
    for (int i = 0; i < numLines; i++){
        DrawRectangle(screenWidth/2 - lineWidth/2, screenHeight/numLines * i, lineWidth, screenHeight/numLines - lineGap, SLIMY_GREEN_L);
    }

    // Walls
    DrawRectangle(0, 0, screenWidth, wallWidth, SLIMY_GREEN_M);
    DrawRectangle(0, screenHeight-16, screenWidth, wallWidth, SLIMY_GREEN_M);

    DrawText(std::to_string(Player1Score).c_str(), screenWidth/2.0f - ScoreOffset.x - 16, ScoreOffset.y, 72, SLIMY_YELLOW);
    DrawText(std::to_string(Player2Score).c_str(), screenWidth/2.0f + ScoreOffset.x - 16, ScoreOffset.y, 72, SLIMY_YELLOW);

    if (Player1){
        Player1->Draw();
    }
    if (Player2){
        Player2->Draw();
    }
    if (GameBall){
        GameBall->Draw();
    }

    EndDrawing();
}

void PongGame::SetRoundTimer(){
    RoundTimer = GetTime() + RoundTimerLength;
}

void PongGame::HandleGoal(const bool bLeft){
    std::printf("Goal!!! %d\n", bLeft ? 0 : 1);
    GameBall->Reset();

    bLeft ? Player2Score++ : Player1Score++;

    // Set timer so the game restarts in a few seconds
    SetRoundTimer();
}
