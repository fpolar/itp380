//
//  Block.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 9/13/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Block.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"
#include "Game.h"
#include "Random.h"
#include "Math.h"
#include <iostream>

Block::Block(Game* game)
:Actor(game){
    mSprite = new SpriteComponent(this);
    
    CollisionComponent* BlockColl = new CollisionComponent(this);
    BlockColl->SetSize(64, 32);
    SetCollisionComponent(BlockColl);
    
    game->AddBlock(this);
}

Block::~Block(){
    mGame->RemoveBlock(this);
}

void Block::ChangeTexture(const char* file){
    mSprite->SetTexture(mGame->getTexture(file));
}
