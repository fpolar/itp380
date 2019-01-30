//
//  BallMove.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 9/13/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Paddle.h"
#include "Ball.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"
#include "Game.h"
#include "Random.h"
#include "BallMove.h"
#include "Math.h"
#include "Block.h"
#include <iostream>

BallMove::BallMove(Actor* actor):MoveComponent(actor){
    velocity = {250, -250};
}

void BallMove::Update(float deltaTime){
    
    mOwner->GetGame()->getBlocks()[0]->GetCollisionComponent();
    int i = 0;
    while(i < mOwner->GetGame()->getBlocks().size() &&
          !mOwner->GetCollisionComponent()->Intersect(mOwner->GetGame()->getBlocks()[i]->GetCollisionComponent())){ i++; }
    
    if(i < mOwner->GetGame()->getBlocks().size()){
        Block* deadBlockWalking = mOwner->GetGame()->getBlocks()[i];
        deadBlockWalking->SetState(Actor::State::EDead);
        
        Vector2 ballToBlock = mOwner->GetPosition() - deadBlockWalking->GetPosition();
        float alpha = Math::Atan2(-ballToBlock.y, ballToBlock.x);
        
        if(alpha > Math::ToRadians(30) && alpha <= Math::ToRadians(150)){
            velocity[1] *= -1;
        }else if(alpha > Math::ToRadians(150) || alpha < Math::ToRadians(-150)){
            velocity[0] *= -1;
        }else if(alpha < Math::ToRadians(30) && alpha >= Math::ToRadians(-30)){
            velocity[0] *= -1;
        }else{
            velocity[1] *= -1;
        }
        
    }
    
    if(velocity[1] > 0 &&
       mOwner->GetCollisionComponent()->Intersect(mOwner->GetGame()->GetPaddle()->GetCollisionComponent())){
        float positionDifference = mOwner->GetPosition().x -
        mOwner->GetGame()->GetPaddle()->GetPosition().x;
        
        float paddleLength = mOwner->GetGame()->GetPaddle()->GetCollisionComponent()->GetWidth();
        
        if(positionDifference <= -paddleLength/6.0f ){
            Vector2 rightNormal = Vector2{-.1f, -.8f};
            rightNormal.Normalize();
            Vector2 reflectedVec = Vector2::Reflect(Vector2{velocity[0], velocity[1]},
                                                    rightNormal);
            velocity[0] = reflectedVec.x;
            velocity[1] = reflectedVec.y;
        }
        else if(positionDifference >= paddleLength/6.0f){
            Vector2 leftNormal = Vector2{.1f, -.8f};
            leftNormal.Normalize();
            Vector2 reflectedVec =Vector2::Reflect(Vector2{velocity[0], velocity[1]},
                                                   leftNormal);
            velocity[0] = reflectedVec.x;
            velocity[1] = reflectedVec.y;
        }else{
            velocity[1] *= -1;
        };
    }
    
    Vector2 ballPos = mOwner->GetPosition();
    
    //ball hits top wall
    if(ballPos.y <= mOwner->GetGame()->GetWallWidth() + ((Ball*)mOwner)->GetRadius()){
        ballPos.y = mOwner->GetGame()->GetWallWidth();
        velocity[1] *= -1;
    }
    
    //ball hits right wall
    if(ballPos.x >= mOwner->GetGame()->GetWindowWidth()-mOwner->GetGame()->GetWallWidth() - ((Ball*)mOwner)->GetRadius()){
        ballPos.x = mOwner->GetGame()->GetWindowWidth()-mOwner->GetGame()->GetWallWidth() - ((Ball*)mOwner)->GetRadius();
        velocity[0] *= -1;
    }
    
    //ball hits left wall
    if(ballPos.x <= mOwner->GetGame()->GetWallWidth() + ((Ball*)mOwner)->GetRadius()){
        ballPos.x = mOwner->GetGame()->GetWallWidth() + ((Ball*)mOwner)->GetRadius();
        velocity[0] *= -1;
    }
    
    //exits screen
    if(ballPos.y > mOwner->GetGame()->GetWindowHeight()){
        Reset();
    }
    
    ballPos = Vector2{
        mOwner->GetPosition().x + velocity[0] * deltaTime,
        mOwner->GetPosition().y + velocity[1] * deltaTime
    };
    mOwner->SetPosition(ballPos);
}

void BallMove::Reset(){
    mOwner->SetPosition(Vector2{mOwner->GetGame()->GetWindowWidth()/2.0f, mOwner->GetGame()->GetWindowHeight() - 75.0f});
    velocity = {250, -250};
}
