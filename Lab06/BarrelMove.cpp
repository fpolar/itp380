#include "BarrelMove.h"
#include "Actor.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "Block.h"
#include "Player.h"
#include <SDL/SDL.h>

BarrelMove::BarrelMove(class Actor* owner)
:MoveComponent(owner)
{
	SetForwardSpeed(100.0f);
	SetAngularSpeed(-Math::TwoPi);
}

void BarrelMove::Update(float deltaTime)
{
	Vector2 pos = mOwner->GetPosition();
	pos.x += GetForwardSpeed() * deltaTime;
	pos.y += mYSpeed * deltaTime;
	mOwner->SetPosition(pos);

	mOwner->SetRotation(mOwner->GetRotation() + GetAngularSpeed() * deltaTime);

	// Do we collide with any blocks?
	for (auto block : mOwner->GetGame()->GetBlocks())
	{
		if (mOwner->GetCollision()->Intersect(block->GetCollision()))
		{
			mYSpeed = 0.0f;
			pos.y = block->GetCollision()->GetMin().y - 16.0f;
			mOwner->SetPosition(pos);
		}
	}

	// Do we collide with the player?
	Player* player = mOwner->GetGame()->GetPlayer();
	if (mOwner->GetCollision()->Intersect(player->GetCollision()))
	{
		player->SetPosition(player->GetStartPos());
	}

	if (pos.y > 768.0f)
	{
		mOwner->SetState(Actor::EDead);
	}
	mYSpeed += 2000.0f * deltaTime;
}
