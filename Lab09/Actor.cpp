#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"
#include "CameraComponent.h"
#include "MeshComponent.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mGame(game)
	,mState(EActive)
	,mPosition(Vector3::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
{
	// TODO
    mGame->AddActor(this);
    mMove = nullptr;
    mCollision = nullptr;
    mMesh = nullptr;
    mCamera = nullptr;
}

Actor::~Actor()
{
	// TODO
    mGame->RemoveActor(this);
    delete mMove;
    delete mCollision;
    delete mMesh;
    delete mCamera;
}

void Actor::Update(float deltaTime)
{
	// TODO
    if(this->mState == EActive){
        if(mMove != nullptr){
            mMove->Update(deltaTime);
        }
        if(mCollision != nullptr){
            mCollision->Update(deltaTime);
        }
        if(mMesh != nullptr){
            mMesh->Update(deltaTime);
        }
        if(mCamera != nullptr){
            mCamera->Update(deltaTime);
        }
        UpdateActor(deltaTime);
    }
    mWorldTransform = Matrix4::CreateScale(mScale)*
                      Matrix4::CreateRotationZ(mRotation)*
                      Matrix4::CreateTranslation(mPosition);
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
        if(mCamera != nullptr){
            mCamera->ProcessInput(keyState);
        }
        ActorInput(keyState);
    }
}

void Actor::ActorInput(const Uint8* keyState)
{
    
}

Vector3 Actor::GetForward() const
{
    return Vector3(Math::Cos(mRotation), Math::Sin(mRotation), 0.0f);
}

Vector3 Actor::GetRight() const
{
    return Vector3(Math::Cos(mRotation + Math::PiOver2),
                   Math::Sin(mRotation + Math::PiOver2),
                   0.0f);
}


