#pragma once
#include "Actor.h"
class BarrelSpawner : public Actor
{
public:
	BarrelSpawner(class Game* game);
	void UpdateActor(float deltaTime) override;
private:
	float mTimer = 3.0f;
};
