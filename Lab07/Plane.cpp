//
//  Plane.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/13/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Plane.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "PlaneMove.h"
#include "Game.h"
#include "Grid.h"
#include "Tile.h"

Plane::Plane(Game* game):Actor(game){
    SetPosition(game->GetGrid()->GetStartTile()->GetPosition());
    
    mSprite = new SpriteComponent(this, 200);
    mSprite->SetTexture(game->GetTexture("Assets/Airplane.png"));
    
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(64, 64);
    
    mMove = new PlaneMove(this);
    
    mGame->AddPlane(this);
}

Plane::~Plane(){
    mGame->RemovePlane(this);
}
