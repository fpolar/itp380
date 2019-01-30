//
//  Asteroid.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 9/11/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//
//

#include "Laser.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "Math.h"
#include "Asteroid.h"
#include <iostream>


Laser::Laser(Game* game)
:Actor(game){
    SpriteComponent* sprite = new SpriteComponent(this);
    sprite->SetTexture(game->getTexture("Assets/Laser.png"));
    this->SetSprite(sprite);
    
    MoveComponent* move = new MoveComponent(this);
    move->SetForwardSpeed(400);
    this->SetMoveComponent(move);
    
    cooldown = 0;
    
}

void Laser::UpdateActor(float deltaTime){
    
    if(cooldown >= 1){
        this->SetState(Actor::State::EDead);
    }
    
    std::vector<Asteroid*> asteroids = mGame->getAsteroids();
    for(int i=0;i<asteroids.size();i++){
        int distance = std::pow(
                                (std::pow( (asteroids[i]->GetPosition().x - GetPosition().x), 2 ) +
                                 std::pow( (asteroids[i]->GetPosition().y - GetPosition().y), 2 )),
                                .5 );
        if(distance <= 70 && this->GetState() != Actor::State::EDead){
            asteroids[i]->SetState(Actor::State::EDead);
            this->SetState(Actor::State::EDead);
        }
    }
}
