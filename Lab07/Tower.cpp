//
//  Tower.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/13/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "Plane.h"
#include "Tower.h"
#include "Bullet.h"
#include "SpriteComponent.h"

Tower::Tower(Game* game)
:Actor(game)
{
    mSprite = new SpriteComponent(this, 200);
    mSprite->SetTexture(game->GetTexture("Assets/Tower.png"));
}

void Tower::UpdateActor(float deltaTime){
    attackTimer -= deltaTime;
    
    if(attackTimer <= 0){
    Plane* target = FindTarget();
        if(target != nullptr){
            Vector2 directionVector = target->GetPosition() - GetPosition();
            if(directionVector.Length() <= 100.0f){
                mRotation = Math::Atan2(-directionVector.y, directionVector.x);
                Bullet* b = new Bullet(mGame);
                b->SetRotation(mRotation);
                b->SetPosition(mPosition);
            }
        }
        attackTimer = attackCooldown;
    }
}

Plane* Tower::FindTarget(){
    float minDistance = Math::Infinity;
    Plane* minPlane = nullptr;
    
    for(auto plane: mGame->GetPlanes()){
        float currentDistance = (plane->GetPosition() - GetPosition()).Length();
        if(minDistance > currentDistance){
            minDistance = currentDistance;
            minPlane = plane;
        }
    }
    
    return minPlane;
}
