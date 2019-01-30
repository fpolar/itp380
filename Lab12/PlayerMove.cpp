#include "PlayerMove.h"
#include "Player.h"
#include "Actor.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "CameraComponent.h"
#include "Block.h"
#include "iostream"
#include <SDL/SDL.h>

PlayerMove::PlayerMove(class Actor* owner)
:MoveComponent(owner)
,mMass(1.0f)
{

	Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Running.wav"), -1);
	Mix_Pause(mRunningSFX);
    ChangeState(PlayerMove::MoveState::Falling);
}

PlayerMove::~PlayerMove() {
	Mix_HaltChannel(mRunningSFX);
}

void PlayerMove::Update(float deltaTime)
{
    switch (mCurrentState) {
        case MoveState::Falling:
            UpdateFalling(deltaTime);
            break;
        case MoveState::Jump:
            UpdateJump(deltaTime);
            break;
        case MoveState::WallClimb:
            UpdateWallClimb(deltaTime);
            break;
        case MoveState::WallRun:
            UpdateWallRun(deltaTime);
            break;
        default:
            UpdateOnGround(deltaTime);
            break;
            
    }
    if(mOwner->GetPosition().z < -750.0f){
        mOwner->SetPosition(((Player*)mOwner)->GetRespawnPosition());
        mOwner->SetRotation(0.0f);
        mVelocity = mPendingForces = Vector3::Zero;
        ChangeState(Falling);
        
    }
	/*If the current state is OnGround and the velocity’s length is > 50.0f or the
		current state is WallClimb or the current state is WallRun, then we want to
		unpause the running sound with :
	Mix_Resume(mRunningSFX);
	▪ Otherwise, pause the running sound*/
	if ((mCurrentState == OnGround && mVelocity.Length() > 50.0f) ||
		(mCurrentState == WallClimb || mCurrentState == WallRun)) {
		Mix_Resume(mRunningSFX);
	}
	else {
		Mix_Pause(mRunningSFX);
	}
}

PlayerMove::CollSide PlayerMove::FixCollision(CollisionComponent* self, CollisionComponent* block){
    
    CollSide out = None;
        if (self->Intersect(block))
        {
            Vector3 pos = mOwner->GetPosition();
            // Get player min/max and block min/max
            Vector3 playerMin = self->GetMin();
            Vector3 playerMax = self->GetMax();
            Vector3 blockMin = block->GetMin();
            Vector3 blockMax = block->GetMax();

            // Figure out which side we are closest to
            float dx1 = blockMin.x - playerMax.x;
            float dx2 = blockMax.x - playerMin.x;
            float dy1 = blockMin.y - playerMax.y;
            float dy2 = blockMax.y - playerMin.y;
            float dz1 = blockMin.z - playerMax.z;
            float dz2 = blockMax.z - playerMin.z;

            float dx = 0.0f;
            if (Math::Abs(dx1) < Math::Abs(dx2))
            {
                dx = dx1;
            }
            else
            {
                dx = dx2;
            }
            
            float dy = 0.0f;
            if (Math::Abs(dy1) < Math::Abs(dy2))
            {
                dy = dy1;
            }
            else
            {
                dy = dy2;
            }
            
            float dz = 0.0f;
            if (Math::Abs(dz1) < Math::Abs(dz2))
            {
                dz = dz1;
                out = Bottom;
            }
            else
            {
                dz = dz2;
                out = Top;
            }

            // Are we closer to top or bottom?
            if (Math::Abs(dz) < Math::Abs(dx) && Math::Abs(dz) < Math::Abs(dy))
            {
                pos.z += dz;
            }
            else if (Math::Abs(dx) < Math::Abs(dy) && Math::Abs(dx) < Math::Abs(dz))
            {
                pos.x += dx;
                if(Math::Abs(dx) == Math::Abs(dx1)){
                    out = SideX1;
                    AddForce(Vector3{-700.0f, 0.0f, 0.0f});
                }
                else{
                    out = SideX2;
                    AddForce(Vector3{700.0f, 0.0f, 0.0f});
                }
            }
            else
            {
                pos.y += dy;
                if(Math::Abs(dy) == Math::Abs(dy1)){
                    out = SideY1;
                    AddForce(Vector3{0.0f, -700.0f, 0.0f});
                }
                else{
                    out = SideY2;
                    AddForce(Vector3{0.0f, 700.0f, 0.0f});
                }
            }
            
            mOwner->SetPosition(pos);
        }
        return out;
}

void PlayerMove::ProcessInput(const Uint8* keyState)
{
    float newForwardSpeed = 0;
    float newStrafeSpeed = 0;
    if(keyState[SDL_SCANCODE_W]){
        newForwardSpeed = 700;
    }
    if(keyState[SDL_SCANCODE_S]){
        newForwardSpeed += -700;
    }
    if(keyState[SDL_SCANCODE_D]){
        newStrafeSpeed = 700;
    }
    if(keyState[SDL_SCANCODE_A]){
        newStrafeSpeed += -700;
    }
    AddForce(mOwner->GetForward()*newForwardSpeed);
    AddForce(mOwner->GetRight()*newStrafeSpeed);
    
    if(!mSpacePressed && keyState[SDL_SCANCODE_SPACE] && mCurrentState == OnGround){
        AddForce(mJumpForce);
        ChangeState(Jump);
		Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Jump.wav"), 0);
    }
    
    mSpacePressed = keyState[SDL_SCANCODE_SPACE];
    
    int x, y;
    SDL_GetRelativeMouseState(&x, &y);
    SetAngularSpeed(x / 500.0f * Math::Pi * 10.0f);
    mOwner->GetCameraComponent()->SetPitchSpeed(y / 500.0f * Math::Pi * 10.0f);
}

void PlayerMove::ChangeState(MoveState m){
    mCurrentState = m;
}

bool PlayerMove::CanWallRun(PlayerMove::CollSide side){
    
    Vector3 normal = Vector3{0,0,1};
    switch (side) {
        case SideX1:
            normal = Vector3{-1,0,0};
            break;
        case SideX2:
            normal = Vector3{1,0,0};
            break;
        case SideY1:
            normal = Vector3{0,-1,0};
            break;
        case SideY2:
            normal = Vector3{0,1,0};
            break;
        default:
            break;
    }
    
    
    Vector3 normal_forward = mOwner->GetForward();
    normal_forward.Normalize();
    float angle = Math::Acos(Vector3::Dot(normal_forward, normal));;
    if(angle < 3*Math::Pi/4
       && (mVelocity.x * mOwner->GetForward()).x > 0
       && (mVelocity.y * mOwner->GetForward()).y > 0
       && (mVelocity*Vector3{1, 1, 0}).Length() >= 350.0f){
        return true;
    }
    
    return false;
}


bool PlayerMove::CanWallClimb(PlayerMove::CollSide side){
    
    Vector3 normal = Vector3{0,0,1};
    switch (side) {
        case SideX1:
            normal = Vector3{-1,0,0};
            break;
        case SideX2:
            normal = Vector3{1,0,0};
            break;
        case SideY1:
            normal = Vector3{0,-1,0};
            break;
        case SideY2:
            normal = Vector3{0,1,0};
            break;
        default:
            break;
    }
    
    Vector3 normal_forward = mOwner->GetForward();
    normal_forward.Normalize();
    float angle = Math::Acos(Vector3::Dot(normal_forward, normal));;
    
    if(angle > 3*Math::Pi/4
       && Vector3::Dot(mVelocity*Vector3{1, 1, 0}, normal) < 0
       && (mVelocity*Vector3{1, 1, 0}).Length() >= 350.0f){
        return true;
    }
    
    return false;
}

void PlayerMove::UpdateOnGround(float deltaTime){
    PhysicsUpdate(deltaTime);
    bool onTop = false;
    for(auto block : mOwner->GetGame()->GetBlocks()){
        CollSide collision = FixCollision(mOwner->GetCollisionComponent(), block->GetCollisionComponent());
        if(collision == Top){
            onTop = true;
        }
        if((collision == SideX1 ||collision == SideX2 || collision == SideY1 || collision == SideY2)
           && CanWallClimb(collision)){
            mWallClimbTimer = 0.0f;
            ChangeState(WallClimb);
            return;
        }
    }
    if(!onTop){
        ChangeState(Falling);
    }
}
void PlayerMove::UpdateJump(float deltaTime){
    PhysicsUpdate(deltaTime);
    mVelocity += mGravity * deltaTime;
    
    for(auto block : mOwner->GetGame()->GetBlocks()){
        CollSide collision = FixCollision(mOwner->GetCollisionComponent(), block->GetCollisionComponent());
        if(collision == Bottom){
            mVelocity.z = 0.0f;
        }
        if((collision == SideX1 ||collision == SideX2 || collision == SideY1 || collision == SideY2)){
            if(CanWallClimb(collision)){
                mWallClimbTimer = 0.0f;
                ChangeState(WallClimb);
                return;
            }else if(CanWallRun(collision)){
                mWallRunTimer = 0.0f;
                ChangeState(WallRun);
                return;
            }
        }
    }
    if(mVelocity.z<=0.0f){
        ChangeState(Falling);
    }
}
void PlayerMove::UpdateFalling(float deltaTime){
    AddForce(mGravity);
    PhysicsUpdate(deltaTime);
    mVelocity += mGravity * deltaTime;
    for(auto block : mOwner->GetGame()->GetBlocks()){
        if(FixCollision(mOwner->GetCollisionComponent(), block->GetCollisionComponent()) == Top){
            mVelocity.z = 0.0f;
			Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Land.wav"), 0);
            ChangeState(OnGround);
        }
    }
}

void PlayerMove::UpdateWallClimb(float deltaTime){
    mWallClimbTimer += deltaTime;
    if(mWallClimbTimer <= 0.4f){
        AddForce(mWallClimbForce);
    }
    
    AddForce(mGravity);
    PhysicsUpdate(deltaTime);
    
    bool collided = false;
    for(auto block : mOwner->GetGame()->GetBlocks()){
        CollSide collision = FixCollision(mOwner->GetCollisionComponent(), block->GetCollisionComponent());
        if((collision == SideX1 ||collision == SideX2 || collision == SideY1 || collision == SideY2)){
            collided = true;
        }
    }
    if(!collided || mVelocity.z <= 0.0f){
        mVelocity.z = 0.0f;
        ChangeState(Falling);
    }
}

void PlayerMove::UpdateWallRun(float deltaTime){
    mWallRunTimer += deltaTime;
    if(mWallRunTimer <= 0.4f){
        AddForce(mWallRunForce);
    }
    
    AddForce(mGravity);
    PhysicsUpdate(deltaTime);
    
    for(auto block : mOwner->GetGame()->GetBlocks()){
        FixCollision(mOwner->GetCollisionComponent(), block->GetCollisionComponent());
    }
    if(mVelocity.z <= 0.0f){
        ChangeState(Falling);
    }
}

void PlayerMove::PhysicsUpdate(float deltaTime){
    mAcceleration = mPendingForces * (1.0f / mMass);
    mVelocity += mAcceleration*deltaTime;
    FixXYVelocity();
    Vector3 pos = mOwner->GetPosition();
    mOwner->SetPosition(pos+mVelocity*deltaTime);
    mOwner->SetRotation(mOwner->GetRotation()+GetAngularSpeed()*deltaTime);
    mPendingForces = Vector3::Zero;
}

void PlayerMove::FixXYVelocity(){
    
    Vector2 xyVelocity = Vector2{mVelocity.x, mVelocity.y};
    if(xyVelocity.Length() > 400.0f){
        xyVelocity.Normalize();
        xyVelocity *= 400.0f; //Make const field for maxspeed
    }
    
    if(mCurrentState == OnGround || mCurrentState == WallClimb){
        if(Math::NearZero(mAcceleration.x) || !(mAcceleration.x * xyVelocity.x >= 0.0f)){
            xyVelocity.x *= 0.9f;
        }
        if(Math::NearZero(mAcceleration.y) || !(mAcceleration.y * xyVelocity.y >= 0.0f)){
            xyVelocity.y *= 0.9f;
        }
    }
    mVelocity.x = xyVelocity.x;
    mVelocity.y = xyVelocity.y;
}
