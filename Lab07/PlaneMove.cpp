//
//  PlaneMove.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/13/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "PlaneMove.h"
#include "Game.h"
#include "Grid.h"
#include "Tile.h"
#include "Actor.h"

PlaneMove::PlaneMove(Actor* actor):MoveComponent(actor){
    SetForwardSpeed(200.0f);
    SetNextTile(actor->GetGame()->GetGrid()->GetStartTile()->GetParent());
}

void PlaneMove::Update(float deltaTime){
    MoveComponent::Update(deltaTime);
    
    if(mNextTile != nullptr &&
       (mOwner->GetPosition() - mNextTile->GetPosition()).Length() < 2.0f){
        SetNextTile(mNextTile->GetParent());
    }
    
    if(mOwner->GetPosition().x > mOwner->GetGame()->GetWindowWidth()){
        mOwner->SetState(Actor::State::EDead);
    }
    
}

void PlaneMove::SetNextTile(const class Tile *t){
    mNextTile = t;
    if(mNextTile == nullptr){
        mOwner->SetRotation(0.0f);
    }else{
        Vector2 direction = t->GetPosition() -  mOwner->GetPosition();
        mOwner->SetRotation(Math::Atan2(-direction.y, direction.x));
    }
}
