//
//  Asteroid.hpp
//  Game-mac
//
//  Created by Pol, Frank A. on 9/11/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//
//

#include "Actor.h"

class Asteroid: public Actor{
public:
    Asteroid(class Game* game);
    ~Asteroid();
    
    // Any actor-specific update code (overridable)
    void UpdateActor(float deltaTime) override;
};
