#include "player.h"

#include <iostream>
#include <ostream>


Player::Player(){
    name = "player0";
}

void Player::BeginPlay(){
    std::cout << "Player::BeginPlay()" << std::endl;
}

void Player::Tick(float DeltaTime){
}
