//
//  Background.h
//  Game-mac
//
//  Created by Pol, Frank A. on 10/4/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//
#include "SpriteComponent.h"
#include <vector>

class Background: public SpriteComponent {
    
public:
    Background(Actor* owner, int drawOrder);
    ~Background();
    void AddImage(SDL_Texture* image){ tiles.push_back(image); }
    void Draw(SDL_Renderer* renderer);
    
    float getParallax(){ return mParallax; }
    void setParallax(float p){ mParallax = p; }
    
private:
    std::vector<SDL_Texture*> tiles;
    
    float mParallax = 1.0f;
};
