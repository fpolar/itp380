//
//  Tank.hpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/23/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//
#include "Actor.h"
#include "Game.h"
#include "Turret.h"

class Tank: public Actor{
public:
    Tank(Game* game);
    void UpdateActor(float deltaTime);
    void SetPlayer2();
    void SetSpawnPosition(Vector3 sp){ mSpawnPosition = sp; }
    void Fire();
    void Respawn();
private:
    Turret* mTurret;
    Vector3 mSpawnPosition;
};
