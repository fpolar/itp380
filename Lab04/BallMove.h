//
//  BallMove.hpp
//  Game-mac
//
//  Created by Pol, Frank A. on 9/13/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//


#include "MoveComponent.h"


class BallMove : public MoveComponent
{
public:
    BallMove(Actor* actor);
    void Update(float deltaTime) override;
    void Reset();
    
private:
    std::vector<float> velocity;
};
