//
//  Tank.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/23/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "Tank.h"
#include "Mesh.h"
#include "Bullet.h"
#include "Renderer.h"
#include "TankMove.h"
#include "MeshComponent.h"
#include "CollisionComponent.h"

Tank::Tank(Game* game):Actor(game){
    mMesh = new MeshComponent(this);
    mMesh->SetMesh(game->GetRenderer()->GetMesh("Assets/TankBase.gpmesh"));
    mMove = new TankMove(this);
    mTurret = new Turret(game);
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(30.0f, 30.0f, 30.0f);
}

void Tank::UpdateActor(float deltaTime){
    mTurret->SetPosition(GetPosition());
}

void Tank::SetPlayer2(){
    ((TankMove*)mMove)->SetPlayer2();
    mTurret->SetPlayer2();
    mMesh->SetTextureIndex(1);
}

void Tank::Respawn(){
    SetPosition(mSpawnPosition);
    SetRotation(0);
    mTurret->SetRotation(0);
}

void Tank::Fire(){
    Bullet* b = new Bullet(mGame);
    b->SetPosition(GetPosition());
    b->SetRotation(mTurret->GetRotation());
    b->SetTank(this);
}
