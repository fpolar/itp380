//
//  PaddleMoveComponent.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 9/13/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//


#include "Paddle.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "PaddleMove.h"
#include <iostream>

PaddleMove::PaddleMove(Actor* actor):MoveComponent(actor){}

void PaddleMove::Update(float deltaTime)
{
    this->MoveComponent::Update(deltaTime);
    if(mOwner->GetPosition().x <= 32 + 104/2){
        mOwner->SetPosition(Vector2{
            32 + 104/2.0f,
            mOwner->GetGame()->GetWindowHeight()-50.0f
        });
    }
    if(mOwner->GetPosition().x >= mOwner->GetGame()->GetWindowWidth()-32-104/2){
        mOwner->SetPosition(Vector2{
            mOwner->GetGame()->GetWindowWidth()-32-104/2.0f,
            mOwner->GetGame()->GetWindowHeight()-50.0f
        });
    }
    
}
