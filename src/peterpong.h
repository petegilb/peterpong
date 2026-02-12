#pragma once
#include <memory>

#include "raylib.h"
#include "player.h"
#include "ball.h"

// https://coolors.co/795c5f-a69658-d9b26f-fadf7f-f2e29f
constexpr Color SMOKYROSE{ 121, 92, 95, 255 };
constexpr Color SAND{166, 150, 88, 255};
constexpr Color SOFTFAWN{217, 178, 111, 255};
constexpr Color JASMINE{250, 223, 127, 255};
constexpr Color VANILLACUSTARD{242, 226, 159, 255};

// https://lospec.com/palette-list/slimy-05
constexpr Color SLIMY_YELLOW{209, 203, 149,255};
constexpr Color SLIMY_GREEN_S{64, 152, 94,255};
constexpr Color SLIMY_GREEN_M{	26, 100, 78,255};
constexpr Color SLIMY_GREEN_L{4, 55, 59,255};
constexpr Color SLIMY_BLUE{10, 26, 47,255};

constexpr int screenWidth = 1280;
constexpr int screenHeight = 960;
constexpr int wallWidth = 16;
constexpr Vector2 ScoreOffset = {screenWidth/16.0f, 32};
constexpr int PointsToWin = 11;

enum class EGameState {
    PreGame,
    MidGame,
    EndGame
};

class PongGame{
public:
    PongGame();
    ~PongGame();

    void StartGame();

    void GameTick();

    void RenderTick();
private:
    // There's always two players.
    std::unique_ptr<Player> Player1;
    std::unique_ptr<Player> Player2;

    std::unique_ptr<Ball> GameBall;

    int Player1Score = 0;
    int Player2Score = 0;

    double RoundTimer = -1;
    const int RoundTimerLength = 2;

    void SetRoundTimer();
    void HandleGoal(bool bLeft);

    EGameState GameState = EGameState::PreGame;

    // Sounds
    Sound GameWinSound;
};
