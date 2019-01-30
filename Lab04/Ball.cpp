//
//  Ball.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 9/13/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Ball.h"
#include "Paddle.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "BallMove.h"
#include "CollisionComponent.h"
#include "Game.h"
#include "Random.h"
#include "Math.h"
#include <iostream>

Ball::Ball(Game* game)
:Actor(game){
    
    SpriteComponent* ballSprite = new SpriteComponent(this, 102);
    ballSprite->SetTexture(game->getTexture("Assets/Ball.png"));
    this->SetSprite(ballSprite);
    
    this->SetMoveComponent(new BallMove(this));
    
    CollisionComponent* ballCollider = new CollisionComponent(this);
    ballCollider->SetSize(20, 20);
    SetCollisionComponent(ballCollider);
}
