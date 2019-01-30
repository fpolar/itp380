//
//  Turret.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/23/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Actor.h"
#include "Game.h"
#include "Bullet.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Turret.h"
#include "MeshComponent.h"
#include "MoveComponent.h"

Turret::Turret(Game* game):Actor(game){
    mMesh = new MeshComponent(this);
    mMesh->SetMesh(game->GetRenderer()->GetMesh("Assets/TankTurret.gpmesh"));
    mMove = new MoveComponent(this);
    
    SetScale(1.8f);
}

void Turret::ActorInput(const Uint8* keyState){
    float newAngularSpeed = 0;
    if(keyState[mClockwiseKey]){
        newAngularSpeed = Math::TwoPi;
    }
    if(keyState[mCounterKey]){
        newAngularSpeed = -Math::TwoPi;
    }
    mMove->SetAngularSpeed(newAngularSpeed);
}

void Turret::SetPlayer2(){
    mClockwiseKey = SDL_SCANCODE_I;
    mCounterKey  = SDL_SCANCODE_P;
    mMesh->SetTextureIndex(1);
}
