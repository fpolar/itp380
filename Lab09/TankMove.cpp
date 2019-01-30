//
//  TankMove.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/23/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Math.h"
#include "Game.h"
#include "Block.h"
#include "Actor.h"
#include "Tank.h"
#include "TankMove.h"
#include "CollisionComponent.h"
#include "MoveComponent.h"
#include <SDL/SDL.h>

TankMove::TankMove(Actor* actor):MoveComponent(actor){};

void TankMove::Update(float deltaTime){
    MoveComponent::Update(deltaTime);
    
    Vector3 pos = mOwner->GetPosition();
    pos.x += GetForwardSpeed() * deltaTime;
////    pos.y += mYSpeed * deltaTime;
//    if (pos.y > 768.0f)
//    {
//        pos.y = 768.0f;
////        mInAir = false;
//    }
//    mOwner->SetPosition(pos);
    
    for (auto block : mOwner->GetGame()->GetBlocks()) 
    {
        // Does the player collide with this block?
        if (mOwner->GetCollisionComponent()->Intersect(block->GetCollisionComponent()))
        {
            // Get player min/max and block min/max
            Vector3 playerMin = mOwner->GetCollisionComponent()->GetMin();
            Vector3 playerMax = mOwner->GetCollisionComponent()->GetMax();
            Vector3 blockMin = block->GetCollisionComponent()->GetMin();
            Vector3 blockMax = block->GetCollisionComponent()->GetMax();
            
            // Figure out which side we are closest to
            float dx1 = blockMin.x - playerMax.x;
            float dx2 = blockMax.x - playerMin.x;
            float dy1 = blockMin.y - playerMax.y;
            float dy2 = blockMax.y - playerMin.y;
            
            float dx = 0.0f;
            if (Math::Abs(dx1) < Math::Abs(dx2))
            {
                dx = dx1;
            }
            else
            {
                dx = dx2;
            }
            
            float dy = 0.0f;
            if (Math::Abs(dy1) < Math::Abs(dy2))
            {
                dy = dy1;
            }
            else
            {
                dy = dy2;
            }
            
            // Are we closer to top or bottom?
            if (Math::Abs(dy) < Math::Abs(dx))
            {
                pos.y += dy;
//                if (dy < 0.0f)
//                {
//                    // Landed on top
//                    mYSpeed = 0.0f;
//                    mInAir = false;
//                }
//                else if (mYSpeed < 0.0f)
//                {
//                    mYSpeed = 0.0f;
//                }
            }
            else
            {
                pos.x += dx;
            }
            
            mOwner->SetPosition(pos);
        }
    }

}

void TankMove::ProcessInput(const Uint8* keyState){
    float newForwardSpeed = 0;
    float newAngularSpeed = 0;
    if(keyState[mForwardKey]){
        newForwardSpeed = 250;
    }
    if(keyState[mBackKey]){
        newForwardSpeed = -250;
    }
    if(keyState[mLeftKey]){
        newAngularSpeed = Math::TwoPi;
    }
    if(keyState[mRightKey]){
        newAngularSpeed = -Math::TwoPi;
    }
    if(!mFired && keyState[mFireKey]){
        ( (Tank*)mOwner)->Fire();
        mFired = true;
    }else if(!keyState[mFireKey]){
        mFired = false;
    }
    SetForwardSpeed(newForwardSpeed);
    SetAngularSpeed(newAngularSpeed);
}

void TankMove::SetPlayer2(){
    mForwardKey = SDL_SCANCODE_O;
    mBackKey  = SDL_SCANCODE_L;
    mLeftKey = SDL_SCANCODE_K;
    mRightKey  = SDL_SCANCODE_SEMICOLON;
    mFireKey = SDL_SCANCODE_RSHIFT;
}
