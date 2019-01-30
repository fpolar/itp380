#include "MoveComponent.h"
#include "Actor.h"

#include <iostream>

MoveComponent::MoveComponent(class Actor* owner)
:Component(owner)
,mAngularSpeed(0.0f)
,mForwardSpeed(0.0f)
,mStrafeSpeed(0.0f)
{
	
}

void MoveComponent::Update(float deltaTime)
{
    mOwner->SetRotation(mAngularSpeed * deltaTime + mOwner->GetRotation());
    
    //Forward Position update
    mOwner->SetPosition(Vector3{
        mOwner->GetPosition().x + mOwner->GetForward().x * mForwardSpeed * deltaTime,
        mOwner->GetPosition().y + mOwner->GetForward().y * mForwardSpeed * deltaTime,
        mOwner->GetPosition().z + mOwner->GetForward().z * mForwardSpeed * deltaTime
    });

    //Strafe Position update
    mOwner->SetPosition(Vector3{
        mOwner->GetPosition().x + mOwner->GetRight().x * mStrafeSpeed * deltaTime,
        mOwner->GetPosition().y + mOwner->GetRight().y * mStrafeSpeed * deltaTime,
        mOwner->GetPosition().z + mOwner->GetRight().z * mStrafeSpeed * deltaTime
    });
}

//Add a mStrafeSpeed, initialized to 0, and make a getter and setter for it
//o In Update, add code that updates the position of the owner based on its right
//vector, the strafe speed, and delta time (this should be separate from the code that
//                                          updates the position based on the forward speed)
