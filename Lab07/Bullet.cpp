//
//  Bullet.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/13/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "Actor.h"
#include "Plane.h"
#include "Bullet.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"

Bullet::Bullet(Game* game):Actor(game){
    mSprite = new SpriteComponent(this, 200);
    mSprite->SetTexture(game->GetTexture("Assets/Bullet.png"));
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(10, 10);
    mMove = new MoveComponent(this);
    mMove->SetForwardSpeed(500.0f);
}

void Bullet::UpdateActor(float deltaTime){
    lifeTimer -= deltaTime;
    if(lifeTimer >= 2.0f){
        SetState(Actor::State::EDead);
        return;
    }
    
    for(auto plane: mGame->GetPlanes()){
        if(mCollision->Intersect(plane->GetCollisionComponent())){
            plane->SetState(Actor::State::EDead);
            SetState(Actor::State::EDead);
        }
    }
}
