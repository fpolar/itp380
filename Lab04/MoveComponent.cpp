#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner)
:Component(owner)
,mAngularSpeed(0.0f)
,mForwardSpeed(0.0f)
{
	
}

void MoveComponent::Update(float deltaTime)
{
    mOwner->SetRotation(mAngularSpeed * deltaTime + mOwner->GetRotation());
    mOwner->SetPosition(Vector2{
        mOwner->GetPosition().x + mOwner->GetForward().x * mForwardSpeed * deltaTime,
        mOwner->GetPosition().y + mOwner->GetForward().y * mForwardSpeed * deltaTime
    });
}
