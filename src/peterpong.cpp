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

    GameState = EGameState::PreGame;
    GameWinSound = LoadSound("resources/winfretless.ogg");
}

PongGame::~PongGame(){
    UnloadSound(GameWinSound);
};

void PongGame::StartGame(){
    if (Player1){
        Player1->BeginPlay();
    }
    if (Player2){
        Player2->BeginPlay();
    }
    Player1Score = 0;
    Player2Score = 0;
}

void PongGame::GameTick(){
    if (GameState == EGameState::PreGame || GameState == EGameState::EndGame){
        if (IsKeyReleased(KEY_SPACE)){
            GameState = EGameState::MidGame;
            StartGame();
            SetRoundTimer();
        }
    }
    else if (GameState == EGameState::MidGame){
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

    if (GameState == EGameState::PreGame){
        DrawText("Press SPACE to start!", 220, screenHeight/2.0f - 64, 72, SLIMY_YELLOW);
    }
    else if (GameState == EGameState::EndGame){
        const std::string winner = Player1Score >= PointsToWin ? "Player 1 Wins!" : "Player 2 Wins!";
        DrawText(winner.c_str(), 240, screenHeight/2.0f - 256, 72, SLIMY_YELLOW);
        DrawText("Press SPACE to restart!", 200, screenHeight/2.0f - 64, 72, SLIMY_YELLOW);
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

    if (Player1Score >= PointsToWin || Player2Score >= PointsToWin){
        GameState = EGameState::EndGame;
        PlaySound(GameWinSound);
        return;
    }

    // Set timer so the game restarts in a few seconds
    SetRoundTimer();
}
