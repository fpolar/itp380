//
//  Coin.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/7/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Coin.h"
#include "SpriteComponent.h"
#include "AnimatedSprite.h"
#include "CollisionComponent.h"
#include "Player.h"
#include "Game.h"
#include "SDL/SDL_image.h"
#include <iostream>

Coin::Coin(Game* game):Actor(game){
    mSprite = new AnimatedSprite(this, 100);
    mSprite->AddImage(game->GetTexture("Assets/Coin/coin1.png"));
    mSprite->AddImage(game->GetTexture("Assets/Coin/coin2.png"));
    mSprite->AddImage(game->GetTexture("Assets/Coin/coin3.png"));
    mSprite->AddImage(game->GetTexture("Assets/Coin/coin4.png"));
    mSprite->AddImage(game->GetTexture("Assets/Coin/coin5.png"));
    mSprite->AddImage(game->GetTexture("Assets/Coin/coin6.png"));
    mSprite->AddImage(game->GetTexture("Assets/Coin/coin7.png"));
    mSprite->AddImage(game->GetTexture("Assets/Coin/coin8.png"));
    mSprite->AddImage(game->GetTexture("Assets/Coin/coin9.png"));
    mSprite->AddImage(game->GetTexture("Assets/Coin/coin10.png"));
    mSprite->AddImage(game->GetTexture("Assets/Coin/coin11.png"));
    mSprite->AddImage(game->GetTexture("Assets/Coin/coin12.png"));
    mSprite->AddImage(game->GetTexture("Assets/Coin/coin13.png"));
    mSprite->AddImage(game->GetTexture("Assets/Coin/coin14.png"));
    mSprite->AddImage(game->GetTexture("Assets/Coin/coin15.png"));
    mSprite->AddImage(game->GetTexture("Assets/Coin/coin16.png"));
    Actor::mSprite = mSprite; 
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(32, 32);
}

void Coin::UpdateActor(float deltaTime){
    if(mGame->GetPlayer()->GetCollision()->Intersect(mCollision)){
        Mix_PlayChannel(-1, mGame->GetSound("Assets/Coin/coin.wav"), 0);
        this->SetState(Actor::State::EDead);
    }

    if(GetPosition().x < mGame->GetCameraPos().x - this->GetSprite()->GetTexWidth()/2) this->SetState(Actor::State::EDead);
}
