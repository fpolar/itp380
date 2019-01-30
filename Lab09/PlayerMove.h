#pragma once
#include "MoveComponent.h"

class PlayerMove : public MoveComponent
{
public:
    enum MoveState{
        OnGround,
        Jump,
        Falling
    };
    enum CollSide{
        None,
        Top,
        Bottom,
        Side
    };
	PlayerMove(class Actor* owner);
	void Update(float deltaTime) override;
    void ProcessInput(const Uint8* keyState) override;
    void ChangeState(MoveState m);
    
protected:
    void UpdateOnGround(float deltaTime);
    void UpdateJump(float deltaTime);
    void UpdateFalling(float deltaTime);
    CollSide FixCollision(class CollisionComponent* self, class CollisionComponent* block);
private:
    MoveState mCurrentState;
    float mZSpeed;
    const float Gravity = -980.0f;
    const float mJumpSpeed = 500.0f;
    
    bool mSpacePressed = false;
};


/*
 
 Add a float mZSpeed member variable, initialized to 0.0f
 o Add a const float Gravity = -980.0f (we’re assuming 1 game unit = 1 cm)
 o In UpdateFalling, after MoveComponent::Update:
 ▪ Update mZSpeed based on Gravity and delta time
 ▪ Update the owner’s z position based on mZSpeed and delta time
 
 */
