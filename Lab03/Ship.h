//
//  Ship.hpp
//  Game-mac
//
//  Created by Pol, Frank A. on 9/11/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "Actor.h"

class Ship: public Actor{
public:
    Ship(class Game* game);
    
    void ActorInput(const Uint8* keyState) override;
    
    void UpdateActor(float deltaTime) override;
    
private:
    float angularAcceleration = 3.1415926535f * .05;
    float forwardAcceleration = 2.5;
    
    float cooldown;
};
