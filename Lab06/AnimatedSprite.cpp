//
//  AnimatedSprite.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/7/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "AnimatedSprite.h"
#include "iostream"

AnimatedSprite::AnimatedSprite(Actor* owner, int drawOrder):SpriteComponent(owner, drawOrder){
}

void AnimatedSprite::Update(float deltaTime){
    
    mAnimTimer += mAnimSpeed*deltaTime;
    if(mAnimTimer >= mImages.size()){
        mAnimTimer = 0.0f;
    }
    this->SetTexture(mImages[int(mAnimTimer)]);
    
    SpriteComponent::Update(deltaTime);
}
