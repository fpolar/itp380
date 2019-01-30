//
//  Block.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/18/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Block.h"
#include "Game.h"
#include "MeshComponent.h"
#include "CollisionComponent.h"
#include "Renderer.h"

Block::Block(Game* game):Actor(game){
    mMesh = new MeshComponent(this);
    mMesh->SetMesh(game->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(1.0f, 1.0f, 1.0f);
    SetScale(64.0f);
    mGame->AddBlock(this);
}

Block::~Block(){
    mGame->RemoveBlock(this);
}
