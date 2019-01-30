//
//  Checkpoint.hpp
//  Game-mac
//
//  Created by ITP on 11/15/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//
#include "Actor.h"
class Checkpoint: public Actor{
public:
    Checkpoint(class Game* game);
    void UpdateActor(float deltaTime) override;
    void ToggleCheckpoint();
    bool active;

	void SetLevelString(std::string l) { mLevelString = l; }
	void SetCheckpointString(std::string l) { mCheckpointString = l; }

private:
	std::string mLevelString;
	std::string mCheckpointString;
};
