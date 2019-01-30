#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mGame(game)
	,mState(EActive)
	,mPosition(Vector2::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
{
	// TODO
    mGame->AddActor(this);
    mSprite = nullptr;
    mMove = nullptr;
}

Actor::~Actor()
{
	// TODO
    mGame->RemoveActor(this);
    delete mSprite;
    delete mMove;
}

void Actor::Update(float deltaTime)
{
	// TODO
    if(this->mState == EActive){
        if(mMove != nullptr){
            mMove->Update(deltaTime);
        }
        if(mSprite != nullptr){
            mSprite->Update(deltaTime);
        }
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::ProcessInput(const Uint8* keyState)
{
    if(this->mState == EActive){
        if(mMove != nullptr){
            mMove->ProcessInput(keyState);
        }
        if(mSprite != nullptr){
            mSprite->ProcessInput(keyState);
        }
        ActorInput(keyState);
    }
}

void Actor::ActorInput(const Uint8* keyState)
{
}

MoveComponent* Actor::GetMoveComponent(){
    return mMove;
}

void Actor::SetMoveComponent(MoveComponent *move){
    mMove = move;
}

SpriteComponent* Actor::GetSprite(){
    return mSprite;
}

void Actor::SetSprite(SpriteComponent *sprite){
    mSprite = sprite;
}

Vector2 Actor::GetForward(){
    return Vector2{cos(mRotation), -sin(mRotation)};
}

