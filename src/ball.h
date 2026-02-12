#pragma once
#include <functional>

#include "player.h"
#include "raylib.h"

constexpr float InitialBallSpeed = 300.f;
constexpr float MaxBallSpeed = 1200.f;
constexpr float BallSpeedStep = 20.f;
constexpr float MaxBounceAngle = 60.f;

class Ball{
public:
    Ball();
    ~Ball();

    void Tick(float DeltaTime);
    void Draw();
    void Move(float DeltaTime);
    void Start();
    void Reset();
    void CalculateVelocity();

    bool bIsInitialized = false;

    Vector2 Position{0.f, 0.f};
    Vector2 InitialPosition;
    Vector2 Velocity{0.f, 0.f};

    float BallWidth = 16.f;
    float BallHeight = 16.f;
    float BallSpeed = InitialBallSpeed;

    Player* Player1 = nullptr;
    Player* Player2 = nullptr;

    std::function<void(bool bLeft)> OnGoal;

    // Sounds
    Sound BallHitSound;
    Sound BallPointSound;
};
