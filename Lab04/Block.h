//
//  Block.hpp
//  Game-mac
//
//  Created by Pol, Frank A. on 9/13/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Actor.h"

class Block: public Actor{
public:
    Block(Game* game);
    ~Block();
    void ChangeTexture(const char* file);
};
