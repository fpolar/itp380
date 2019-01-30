#include "Barrel.h"
#include "SpriteComponent.h"
#include "BarrelMove.h"
#include "Game.h"
#include "CollisionComponent.h"

Barrel::Barrel(class Game* game)
:Actor(game)
{
	mSprite = new SpriteComponent(this, 150);
	mSprite->SetTexture(GetGame()->GetTexture("Assets/Barrel.png"));
	mMove = new BarrelMove(this);
	
	mCollision = new CollisionComponent(this);
	mCollision->SetSize(32.0f, 32.0f);
}
