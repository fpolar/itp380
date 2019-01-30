//
//  Turret.hpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/23/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//
#include "Game.h"
#include "Actor.h"
#include <SDL/SDL.h>

class Turret: public Actor{
public:
    Turret(Game* game);
    void ActorInput(const Uint8* keyState);
    void SetPlayer2();
private:
    int mClockwiseKey = SDL_SCANCODE_Q;
    int mCounterKey = SDL_SCANCODE_E;
    int mFireKey = SDL_SCANCODE_LSHIFT;
    
    bool mFired;
};
