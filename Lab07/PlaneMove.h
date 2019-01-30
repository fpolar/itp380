//
//  PlaneMove.hpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/13/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//
#include "MoveComponent.h"

class PlaneMove: public MoveComponent{
public:
    PlaneMove(Actor* actor);
    
    void Update(float deltaTime) override;
    
    void SetNextTile(const class Tile* t);
    
private:
    const class Tile* mNextTile;
};
