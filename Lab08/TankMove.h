//
//  TankMove.hpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/23/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "MoveComponent.h"
#include <SDL/SDL.h>

class TankMove: public MoveComponent{
public:
    TankMove(Actor* actor);
    void Update(float deltaTime) override;
    void ProcessInput(const Uint8* keyState) override;
    void SetPlayer2();
    void ActorInput(const Uint8* keyState);
    
    bool mFired = false;
    
private:
    int mForwardKey = SDL_SCANCODE_W;
    int mBackKey = SDL_SCANCODE_S;
    int mLeftKey = SDL_SCANCODE_A;
    int mRightKey = SDL_SCANCODE_D;
    int mFireKey = SDL_SCANCODE_LSHIFT;
};
