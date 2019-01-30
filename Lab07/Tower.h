//
//  Tower.hpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/13/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Actor.h"

class Tower: public Actor{
public:
    Tower(Game* game);
    
    void UpdateActor(float deltaTime) override;
    class Plane* FindTarget();
private:
    float attackCooldown = 2.0f;
    float attackTimer = 2.0f;
};
