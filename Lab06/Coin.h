//
//  Coin.hpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/7/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Actor.h"
#include "AnimatedSprite.h"
class Coin : public Actor
{
public:
    Coin(class Game* game);
    void UpdateActor(float deltaTime);
private:
    AnimatedSprite* mSprite;
};
