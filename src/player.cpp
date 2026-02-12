#include "player.h"

#include <iostream>
#include <ostream>

#include "peterpong.h"
#include "raymath.h"


Player::Player(){
    name = "player0";
    PaddleTexture = LoadTexture("resources/Paddle.png");
}

Player::~Player(){
    UnloadTexture(PaddleTexture);
}

void Player::BeginPlay(){
    std::cout << "Player::BeginPlay()" << std::endl;

    bIsInitialized = true;

    if (bIsPlayer1){
        Position.x = PaddleXOffset;
        Position.y = screenHeight/2.0 - PaddleHeight/2.0f;
    }
    else{
        Position.x = screenWidth - PaddleXOffset - PaddleWidth;
        Position.y = screenHeight/2.0 - PaddleHeight/2.0f;
    }
}

void Player::Tick(float DeltaTime){
    if (!bIsInitialized) return;

    if (bIsPlayer1){
        if (IsKeyDown(KEY_W)) Move(-MoveSpeed * DeltaTime);
        if (IsKeyDown(KEY_S)) Move(MoveSpeed * DeltaTime);
    }
    else{
        if (IsKeyDown(KEY_UP)) Move(-MoveSpeed * DeltaTime);
        if (IsKeyDown(KEY_DOWN)) Move(MoveSpeed * DeltaTime);
    }
}

void Player::Draw(){
    if (!bIsInitialized) return;
    DrawTextureV(PaddleTexture, Position, SLIMY_GREEN_S);
}

void Player::Move(float Distance){
    Position.y += Distance;
    Position.y = Clamp(Position.y, wallWidth, screenHeight-wallWidth-PaddleHeight);
}
