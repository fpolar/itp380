//
//  Ball.hpp
//  Game-mac
//
//  Created by Pol, Frank A. on 9/13/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//


#include "Actor.h"

class Ball: public Actor{
public:
    
    Ball(Game* game);
    int GetRadius(){ return radius; }
    
private:
    int radius = 11;
    std::vector<float> velocity;
};
