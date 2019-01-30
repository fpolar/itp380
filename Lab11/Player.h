//
//  Player.hpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/25/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//


#include "Actor.h"

class Player: public Actor{
public:
    Player(class Game* game);
    void SetRespawnPosition(Vector3 pos){ mRespawnPosition = pos;}
    Vector3 GetRespawnPosition(){ return mRespawnPosition;}
private:
    Vector3 mRespawnPosition = Vector3{0.0f, 0.0f, 0.0f};
};
