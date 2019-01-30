#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"
#include "iostream"

Actor::Actor(Game* game)
	:mGame(game)
	,mState(EActive)
	,mPosition(Vector2::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
	,mSprite(nullptr)
	,mMove(nullptr)
	,mCollision(nullptr)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	delete mSprite;
	delete mMove;
	delete mCollision;
	mGame->RemoveActor(this);
}

void Actor::Update(float deltaTime)
{
	if (mState == EActive)
	{
		// Update move component
		if (mMove)
		{
			mMove->Update(deltaTime);
		}
		// Update sprite component
		if (mSprite)
		{
			mSprite->Update(deltaTime);
		}
		if (mCollision)
		{
			mCollision->Update(deltaTime);
		}
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::ProcessInput(const Uint8* keyState)
{
	if (mState == EActive)
	{
		// Process input for move component
		if (mMove)
		{
			mMove->ProcessInput(keyState);
		}
		// Process input for sprite component
		if (mSprite)
		{
			mSprite->ProcessInput(keyState);
		}
		if (mCollision)
		{
			mCollision->ProcessInput(keyState);
		}
		// Process actor input
		ActorInput(keyState);
	}
}

void Actor::ActorInput(const Uint8* keyState)
{
	
}
