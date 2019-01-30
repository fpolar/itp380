//
//  Ship.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 9/11/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Ship.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Laser.h"
#include <iostream>

Ship::Ship(Game* game)
:Actor(game){
    SpriteComponent* shipSprite = new SpriteComponent(this);
    shipSprite->SetTexture(game->getTexture("Assets/Ship.png"));  
    this->SetSprite(shipSprite);
    
    this->SetMoveComponent(new MoveComponent(this));
    
    cooldown = 0;
}

/*The instructions were pretty open ended on the texture switching,
 I thought that maybe things like this should be done in process input,
 but I thought it'd be quicker here and the instructions did not say to do so
*/
void Ship::ActorInput(const Uint8 *keyState){
    
    if(keyState[SDL_SCANCODE_UP]){
        mMove->incrementForwardSpeed(forwardAcceleration);
        GetSprite()->SetTexture(mGame->getTexture("Assets/ShipThrust.png"));
    }
    else if(keyState[SDL_SCANCODE_DOWN]){
        mMove->incrementForwardSpeed(-forwardAcceleration);
        GetSprite()->SetTexture(mGame->getTexture("Assets/ShipThrust.png"));
    }
    else{
        mMove->SetForwardSpeed(0);
        GetSprite()->SetTexture(mGame->getTexture("Assets/Ship.png"));
    }
    
    if(keyState[SDL_SCANCODE_LEFT]){
        mMove->incrementAngularSpeed(angularAcceleration);
    }
    else if(keyState[SDL_SCANCODE_RIGHT]){
        mMove->incrementAngularSpeed(-angularAcceleration);
    }
    else{
        mMove->SetAngularSpeed(0);
    }
    
    if(keyState[SDL_SCANCODE_SPACE] && cooldown >= 1){
        Laser* l = new Laser(mGame);
        l->SetRotation(this->GetRotation());
        l->SetPosition(this->GetPosition());
        cooldown = 0;
    }
}

void Ship::UpdateActor(float deltaTime){
    cooldown += deltaTime;
    
    Vector2 pos = GetPosition();
    if(pos.x < 0){
        SetPosition(Vector2{1.0f * mGame->getWindowWidth(), pos.y});
    }
    if(pos.y < 0){
        SetPosition(Vector2{1.0f * pos.x, 1.0f * mGame->getWindowHeight()});
    }
    if(pos.x > mGame->getWindowWidth()){
        SetPosition(Vector2{0, pos.y});
    }
    if(pos.y > mGame->getWindowHeight()){
        SetPosition(Vector2{pos.x, 0});
    }
}
