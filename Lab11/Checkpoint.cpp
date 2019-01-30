//
//  Checkpoint.cpp
//  Game-mac
//
//  Created by ITP on 11/15/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Checkpoint.h"
#include "Game.h"
#include "Player.h"
#include "MeshComponent.h"
#include "CollisionComponent.h"
#include "Renderer.h"

Checkpoint::Checkpoint(Game* game):Actor(game){
    active = false;
    mMesh = new MeshComponent(this);
    mMesh->SetMesh(game->GetRenderer()->GetMesh("Assets/Checkpoint.gpmesh"));
    mMesh->SetTextureIndex(1);
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(25.0f, 25.0f, 25.0f);
    game->PushCheckpoint(this);
}

void Checkpoint::UpdateActor(float deltaTime){
    if(active &&
       mCollision->Intersect(mGame->GetPlayer()->GetCollisionComponent())){
		Mix_PlayChannel(-1, mGame->GetSound("Assets/Sounds/Checkpoint.wav"), 0);
        ToggleCheckpoint();

		if (mLevelString != "") {
			mGame->SetNextLevel(mLevelString);
		}
    }
}

void Checkpoint::ToggleCheckpoint(){
//    while(mGame->CurrentCheckpoint() != this){
//        mGame->PopCheckpoint();
//    }
    mGame->GetPlayer()->SetRespawnPosition(mGame->CurrentCheckpoint()->GetPosition());
    mGame->PopCheckpoint();
    if(mGame->CurrentCheckpoint() != nullptr){
        mGame->CurrentCheckpoint()->active = true;
        mGame->CurrentCheckpoint()->GetMesh()->SetTextureIndex(0);
    }
}
