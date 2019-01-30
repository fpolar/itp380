//
//  Paddle.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 9/13/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Paddle.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"
#include "PaddleMove.h"
#include "Game.h"
#include "Random.h"
#include "Math.h"
#include <iostream>

Paddle::Paddle(Game* game)
:Actor(game){
    
    SpriteComponent* paddleSprite = new SpriteComponent(this, 101);
    paddleSprite->SetTexture(game->getTexture("Assets/Paddle.png"));
    this->SetSprite(paddleSprite);
    
    this->SetMoveComponent(new PaddleMove(this));
    
    CollisionComponent* paddleCollider = new CollisionComponent(this);
    paddleCollider->SetSize(104, 24);
    SetCollisionComponent(paddleCollider);
}


void Paddle::ActorInput(const Uint8 *keyState){
    
    if(keyState[SDL_SCANCODE_LEFT]){
        mMove->SetForwardSpeed(-speed);
    }
    else if(keyState[SDL_SCANCODE_RIGHT]){
        mMove->SetForwardSpeed(speed);
    }
    else{
        mMove->SetForwardSpeed(0);
    }
}

//void Paddle::UpdateActor(float deltaTime){
//    
//    Vector2 pos = GetPosition();
//    if(pos.x < 0){
//        SetPosition(Vector2{1.0f * mGame->getWindowWidth(), pos.y});
//    }
//    if(pos.y < 0){
//        SetPosition(Vector2{1.0f * pos.x, 1.0f * mGame->getWindowHeight()});
//    }
//    if(pos.x > mGame->getWindowWidth()){
//        SetPosition(Vector2{0, pos.y});
//    }
//    if(pos.y > mGame->getWindowHeight()){
//        SetPosition(Vector2{pos.x, 0});
//    }
//}
