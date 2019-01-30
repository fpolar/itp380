//
//  Asteroid.hpp
//  Game-mac
//
//  Created by Pol, Frank A. on 9/11/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//
//

#include "Actor.h"

class Laser: public Actor{
public:
    Laser(class Game* game);
    
    // Any actor-specific update code (overridable)
    void UpdateActor(float deltaTime) override;
    
private:
    float cooldown;
    
};
