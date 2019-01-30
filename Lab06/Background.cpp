//
//  Background.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/4/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Background.h"
#include "Actor.h"
#include "Game.h"
#include "SDL/SDL.h"
#include <iostream>

Background::Background(Actor* owner, int drawOrder)
:SpriteComponent(owner, drawOrder){
    
}

Background::~Background(){
    while (!tiles.empty())
    {
        delete tiles.back();
    }
    tiles.clear();
}

void Background::Draw(SDL_Renderer* renderer){
    Vector2 pos = mOwner->GetPosition() - mParallax*(mOwner->GetGame()->GetCameraPos());

    int i = 0;
    SDL_Texture* tile = tiles[i];
//    
//    while(pos.x +  < mOwner->GetGame()->GetCameraPos().x){
//        tile = tiles[i];
//        SDL_QueryTexture(tile, nullptr, nullptr, &mTexWidth, &mTexHeight);
//        pos.x += mTexWidth;
//        i++;
//    }

    while(pos.x < 1024){
        tile = tiles[i];
        SDL_QueryTexture(tile, nullptr, nullptr, &mTexWidth, &mTexHeight);

        SDL_Rect r;
        r.w = static_cast<int>(mTexWidth);
        r.h = static_cast<int>(mTexHeight);
        r.x = static_cast<int>(pos.x);
        r.y = static_cast<int>(pos.y);

        SDL_RenderCopyEx(renderer,
                         tile,
                         nullptr,
                         &r,
                         -Math::ToDegrees(mOwner->GetRotation()),
                         nullptr,
                         SDL_FLIP_NONE);

        pos += Vector2{r.w*1.0f, 0};

        if(++i >= tiles.size()) i = 0;
    }
}
