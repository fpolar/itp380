//
//  AnimatedSprite.h
//  Game-mac
//
//  Created by Pol, Frank A. on 10/7/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"
#include "SpriteComponent.h"
#include <vector>

class AnimatedSprite : public SpriteComponent 
{
public:
    AnimatedSprite(class Actor* owner, int drawOrder);
    void Update(float deltaTime) override;
    void AddImage(SDL_Texture* image){ mImages.push_back(image); }
private:
    std::vector<SDL_Texture*> mImages;
    float mAnimTimer = 0.0f;
    float mAnimSpeed = 15.0f;
};
