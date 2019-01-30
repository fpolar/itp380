#include "BarrelSpawner.h"
#include "Game.h"
#include "Barrel.h"

BarrelSpawner::BarrelSpawner(class Game* game)
:Actor(game)
{
}

void BarrelSpawner::UpdateActor(float deltaTime)
{
	mTimer -= deltaTime;
	if (mTimer <= 0.0f)
	{
		Barrel* b = new Barrel(GetGame());
		b->SetPosition(GetPosition());
		mTimer = 3.0f;
	}
}
