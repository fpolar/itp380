//
//  Bullet.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/23/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "Block.h"
#include "Bullet.h"
#include "Renderer.h"
#include "TankMove.h"
#include "Tank.h"
#include "MoveComponent.h"
#include "MeshComponent.h"
#include "CollisionComponent.h"

Bullet::Bullet(Game* game):Actor(game){
    SetScale(0.5f);
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(1.0f, 1.0f, 1.0f);
    mMove = new MoveComponent(this);
    mMove->SetForwardSpeed(400.0f);
    mMesh = new MeshComponent(this);
    mMesh->SetMesh(game->GetRenderer()->GetMesh("Assets/Sphere.gpmesh"));
}


void Bullet::UpdateActor(float deltaTime){
    for (auto block : mGame->GetBlocks())
    {
        if (GetCollisionComponent()->Intersect(block->GetCollisionComponent()))
        {
            SetState(Actor::State::EDead);
            return;
        }
    }
    if (mGame->getTank1() != mTank &&
        GetCollisionComponent()->Intersect(mGame->getTank1()->GetCollisionComponent()))
    {
        mGame->getTank1()->Respawn();
        SetState(Actor::State::EDead);
        return;
    }
    if (mGame->getTank2() != mTank &&
        GetCollisionComponent()->Intersect(mGame->getTank2()->GetCollisionComponent()))
    {
        mGame->getTank2()->Respawn();
        SetState(Actor::State::EDead);
        return;
    }
    
}
