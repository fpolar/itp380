//
//  Bullet.hpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/23/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Actor.h"

class Bullet: public Actor{
public:
    Bullet(class Game* game);
    void SetTank(class Tank* tank){ mTank = tank; };
    void UpdateActor(float deltaTime) override;
private:
    class Tank* mTank;
};
