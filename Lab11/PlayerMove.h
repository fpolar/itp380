#pragma once
#include "Math.h"
#include "MoveComponent.h"

class PlayerMove : public MoveComponent
{
public:
    enum MoveState{
        OnGround,
        Jump,
        Falling,
        WallClimb,
        WallRun
    };
    enum CollSide{
        None,
        Top,
        Bottom,
        SideX1,
        SideX2,
        SideY1,
        SideY2
    };
	PlayerMove(class Actor* owner);
	~PlayerMove();
	void Update(float deltaTime) override;
    void ProcessInput(const Uint8* keyState) override;
    void ChangeState(MoveState m);
    
    void PhysicsUpdate(float deltaTime);
    void AddForce(const Vector3& force){ mPendingForces+=force; }
    void FixXYVelocity();
    
protected:
    void UpdateOnGround(float deltaTime);
    void UpdateJump(float deltaTime);
    void UpdateFalling(float deltaTime);
    void UpdateWallClimb(float deltaTime);
    void UpdateWallRun(float deltaTime);
    bool CanWallClimb(CollSide side);
    bool CanWallRun(CollSide side);
    CollSide FixCollision(class CollisionComponent* self, class CollisionComponent* block);
private:
    
    MoveState mCurrentState;
    
    Vector3 mVelocity, mAcceleration, mPendingForces;
    
    float mMass;
    
    Vector3 mGravity = Vector3{0.0f, 0.0f, -980.0f};
    Vector3 mJumpForce = Vector3{0.0f, 0.0f, 35000.0f};
    Vector3 mWallClimbForce = Vector3{0.0f, 0.0f, 1800.0f};
    Vector3 mWallRunForce = Vector3{0.0f, 0.0f, 1200.0f};
    
    bool mSpacePressed = false;
    float mWallClimbTimer = 0.0f;
    float mWallRunTimer = 0.0f;

	int mRunningSFX = 0;
};
