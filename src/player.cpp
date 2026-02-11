#include "player.h"

#include <iostream>
#include <ostream>

#include "peterpong.h"


Player::Player(){
    name = "player0";
    PaddleTexture = LoadTexture("resources/Paddle.png");
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

}

void Player::Draw(){
    if (!bIsInitialized) return;
    DrawTextureV(PaddleTexture, Position, SLIMY_GREEN_S);
}
