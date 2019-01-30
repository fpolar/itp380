//
//  Bullet.hpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/13/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

class Bullet: public Actor{
public:
    Bullet(Game* game);
    void UpdateActor(float deltaTime) override;
    
private:
    float lifespan = 2.0f;
    float lifeTimer = lifespan;
};
