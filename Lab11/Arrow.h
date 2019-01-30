//
//  Arrow.hpp
//  Game-mac
//
//  Created by ITP on 11/15/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//


#include "Actor.h"
class Arrow: public Actor{
public:
    Arrow(class Game* game);
    void UpdateActor(float deltaTime) override;
};
