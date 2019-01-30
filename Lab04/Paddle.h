//
//  Paddle.hpp
//  Game-mac
//
//  Created by Pol, Frank A. on 9/13/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Actor.h"

class Paddle: public Actor{
public:
    
    Paddle(Game* game);
    void ActorInput(const Uint8 *keyState);

    
private:
    float speed = 250;
};
