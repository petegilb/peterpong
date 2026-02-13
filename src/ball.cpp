
#include "ball.h"

#include <iostream>

#include "peterpong.h"
#include "raymath.h"

Ball::Ball(){
    Position = Vector2{screenWidth/2.f - BallWidth/2.f, screenHeight/2.f - BallHeight/2.f};
    Velocity = Vector2(0.f, 0.f);
    InitialPosition = Position;

    // Load Sounds
    BallHitSound = LoadSound("resources/peterpong_hit.wav");
    BallPointSound = LoadSound("resources/peterpong_point.wav");
}

Ball::~Ball(){
    // Unload Sounds
    UnloadSound(BallHitSound);
    UnloadSound(BallPointSound);
}

void Ball::Tick(float DeltaTime){
    if (IsKeyPressed(KEY_F)){
        Position = Vector2{screenWidth/2.f - BallWidth/2.f, screenHeight/2.f - BallHeight/2.f};
        Start();
    }
    CalculateVelocity();
    Move(DeltaTime);
}

void Ball::Draw(){
    if (!bIsInitialized) return;
    DrawRectangleV(Position, Vector2(BallWidth, BallHeight), SLIMY_YELLOW);
}

void Ball::Move(float DeltaTime){
    if (!bIsInitialized) return;
    Position += Velocity * DeltaTime;
}

void Ball::Start(){
    bIsInitialized = true;

    // 2D Direction vector is on a Unit circle (a unit vector)
    // any point on a unit circle is: x = cos(theta aka angle in radians), y = sin(theta)
    const float maxAngle = MaxBounceAngle * DEG2RAD;
    const float randNorm = static_cast<float>(GetRandomValue(0, 10000)) / 10000.0f;
    float angle = Lerp(-maxAngle, maxAngle, randNorm);

    // Flip direction toward left player by adding PI (180 degrees)
    if (GetRandomValue(0, 1)){
        angle += PI;
    }

    const Vector2 dir = { std::cos(angle), std::sin(angle) };
    Velocity = dir * InitialBallSpeed;
    PlaySound(BallHitSound);
}

void Ball::Reset(){
    Velocity = Vector2{0.f, 0.f};
    Position = InitialPosition;
    bIsInitialized = false;
    BallSpeed = InitialBallSpeed;
}

void Ball::CalculateVelocity(){
    if (!bIsInitialized) return;

    // Need to check if the ball is colliding with anything

    Rectangle BallRec = { Position.x, Position.y, BallWidth, BallHeight };

    // Check walls
    Rectangle RightWall = { screenWidth - 4, 0, 4, screenHeight };
    Rectangle LeftWall = { 0, 0, 4, screenHeight };
    bool bHitRightWall = CheckCollisionRecs(BallRec, RightWall);
    bool bHitLeftWall = CheckCollisionRecs(BallRec, LeftWall);

    // If we hit a wall, a player wins a point
    if (bHitRightWall || bHitLeftWall){
        Velocity = Vector2{0.f, 0.f};
        if (OnGoal){
            OnGoal(bHitLeftWall);
        }
        PlaySound(BallPointSound);
        return;
    }

    if (!(Player1 && Player2)) return;

    // if we hit a paddle, bounce back
    Rectangle Player1Paddle = { Player1->Position.x, Player1->Position.y, PaddleWidth, PaddleHeight };
    Rectangle Player2Paddle = { Player2->Position.x, Player2->Position.y, PaddleWidth, PaddleHeight };

    bool bHitPlayer1 = CheckCollisionRecs(BallRec, Player1Paddle);
    bool bHitPlayer2 = CheckCollisionRecs(BallRec, Player2Paddle);

    if (bHitPlayer1 || bHitPlayer2){
        // std::cout << "Hit player!" << std::endl;
        Player* HitPlayer = bHitPlayer1 ? Player1 : Player2;
        float paddleCenter = HitPlayer->Position.y + PaddleHeight * 0.5f;
        float ballCenter = Position.y + BallHeight * 0.5f;

        // get the center of both and find where they intersect, then normalize from -1 to 1
        float relativeIntersectY = ballCenter - paddleCenter;
        float normalized = relativeIntersectY / (PaddleHeight * 0.5f);
        normalized = Clamp(normalized, -1.0f, 1.0f);

        // construct the new direction vector using the same unit circle method from Start()
        float maxBounceAngle = MaxBounceAngle * DEG2RAD;
        float bounceAngle = normalized * maxBounceAngle;

        const Vector2 dir = { std::cos(bounceAngle), std::sin(bounceAngle) };
        // Increase ball speed by the step amount
        BallSpeed += BallSpeedStep;
        BallSpeed = Clamp(BallSpeed, InitialBallSpeed, MaxBallSpeed);
        Velocity = dir * BallSpeed;
        if (bHitPlayer2) Velocity.x *= -1;

        PlaySound(BallHitSound);
        return;
    }

    Rectangle TopWall = { 0, 0, screenWidth, wallWidth };
    Rectangle BottomWall = { 0, screenHeight - wallWidth, screenWidth, wallWidth };

    bool bHitTopWall = CheckCollisionRecs(BallRec, TopWall);
    bool bHitBottomWall = CheckCollisionRecs(BallRec, BottomWall);

    if (bHitTopWall && Velocity.y <= 1){
        Velocity.y *= -1;
        PlaySound(BallHitSound);
    }
    else if (bHitBottomWall && Velocity.y >= 1){
        Velocity.y *= -1;
        PlaySound(BallHitSound);
    }


}
