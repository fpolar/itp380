//
//  Player.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/25/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "Player.h"
#include "PlayerMove.h"
#include "CollisionComponent.h"
#include "CameraComponent.h"

Player::Player(Game* game):Actor(game){
    mMove = new PlayerMove(this);
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(50.0f, 175.0f, 50.0f);
    mCamera = new CameraComponent(this);
}
