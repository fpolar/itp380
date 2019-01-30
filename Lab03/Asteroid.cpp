//
//  Asteroid.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 9/11/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//
//

#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "Math.h"
#include <iostream>


Asteroid::Asteroid(Game* game)
:Actor(game){
    game->AddAsteroid(this);
    
    SpriteComponent* sprite = new SpriteComponent(this);
    sprite->SetTexture(game->getTexture("Assets/Asteroid.png"));
    this->SetSprite(sprite);
    
    MoveComponent* move = new MoveComponent(this);
    move->SetForwardSpeed(150);
    this->SetMoveComponent(move);
    
    SetRotation(Random::GetFloatRange(0, Math::TwoPi));
    SetPosition(Random::GetVector(Vector2{0,0},
                                  Vector2{1.0f * mGame->getWindowWidth(), 1.0f * mGame->getWindowHeight()}));
}

Asteroid::~Asteroid() {
    mGame->RemoveAsteroid(this);
}

void Asteroid::UpdateActor(float deltaTime){
    Vector2 pos = GetPosition();
    if(pos.x < 0){
        SetPosition(Vector2{1.0f * mGame->getWindowWidth(), pos.y});
    }
    if(pos.y < 0){
        SetPosition(Vector2{1.0f * pos.x, 1.0f * mGame->getWindowHeight()});
    }
    if(pos.x > mGame->getWindowWidth()){
        SetPosition(Vector2{0, pos.y});
    }
    if(pos.y > mGame->getWindowHeight()){
        SetPosition(Vector2{pos.x, 0});
    }
}
