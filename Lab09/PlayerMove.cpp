#include "PlayerMove.h"
#include "Actor.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "CameraComponent.h"
#include "Block.h"
#include "iostream"
#include <SDL/SDL.h>

PlayerMove::PlayerMove(class Actor* owner)
:MoveComponent(owner)
,mZSpeed(0.0f)
{
    ChangeState(PlayerMove::MoveState::Falling);
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
        default:
            UpdateOnGround(deltaTime);
            break;
            
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
                out = Side;
            }
            else
            {
                pos.y += dy;
                out = Side;
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
        newForwardSpeed = 350;
    }
    if(keyState[SDL_SCANCODE_S]){
        newForwardSpeed += -350;
    }
    if(keyState[SDL_SCANCODE_D]){
        newStrafeSpeed = 350;
    }
    if(keyState[SDL_SCANCODE_A]){
        newStrafeSpeed += -350;
    }
    SetForwardSpeed(newForwardSpeed);
    SetStrafeSpeed(newStrafeSpeed);
    
    if(!mSpacePressed && keyState[SDL_SCANCODE_SPACE] && mCurrentState == OnGround){
        mZSpeed = mJumpSpeed;
        ChangeState(Jump);
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


void PlayerMove::UpdateOnGround(float deltaTime){
    MoveComponent::Update(deltaTime);
    bool onTop = false;
    for(auto block : mOwner->GetGame()->GetBlocks()){
        if(FixCollision(mOwner->GetCollisionComponent(), block->GetCollisionComponent()) == Top){
            onTop = true;
        }
    }
    if(!onTop){
        ChangeState(Falling);
    }
}
void PlayerMove::UpdateJump(float deltaTime){
    MoveComponent::Update(deltaTime);
    mZSpeed += Gravity * deltaTime;
    Vector3 pos = mOwner->GetPosition();
    mOwner->SetPosition(pos + Vector3{0,0,mZSpeed * deltaTime});
    for(auto block : mOwner->GetGame()->GetBlocks()){
        if(FixCollision(mOwner->GetCollisionComponent(), block->GetCollisionComponent()) == Bottom){
            mZSpeed = 0.0f;
        }
    }
    if(mZSpeed<=0.0f){
        ChangeState(Falling);
    }
}
void PlayerMove::UpdateFalling(float deltaTime){
    MoveComponent::Update(deltaTime);
    mZSpeed += Gravity * deltaTime;
    Vector3 pos = mOwner->GetPosition();
    mOwner->SetPosition(pos + Vector3{0,0,mZSpeed*deltaTime});
    for(auto block : mOwner->GetGame()->GetBlocks()){
        if(FixCollision(mOwner->GetCollisionComponent(), block->GetCollisionComponent()) == Top){
            mZSpeed = 0.0f;
            ChangeState(OnGround);
        }
    }
}
