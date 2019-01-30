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
	if (mAngularSpeed)
	{
		float rot = mOwner->GetRotation();
		rot += mAngularSpeed * deltaTime;
		mOwner->SetRotation(rot);
	}
	
	if (mForwardSpeed)
	{
		Vector2 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;		
		mOwner->SetPosition(pos);
	}
}
