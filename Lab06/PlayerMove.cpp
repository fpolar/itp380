#include "PlayerMove.h"
#include "Actor.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "Block.h"
#include <SDL/SDL.h>

PlayerMove::PlayerMove(class Actor* owner)
:MoveComponent(owner)
{
    SetForwardSpeed(300.0f);
}

void PlayerMove::Update(float deltaTime)
{
	Vector2 pos = mOwner->GetPosition();
    
    mAirtime += deltaTime;
    if( mAirtime < 300.0f && mSpacePressed ){
        mYSpeed -= 1500.0f*deltaTime;
    }
    
	pos.x += GetForwardSpeed() * deltaTime;
	pos.y += mYSpeed * deltaTime;
	if (pos.y > 768.0f)
	{
		pos.y = 768.0f;
		mInAir = false;
	}
	mOwner->SetPosition(pos);
    
    float edge = mOwner->GetGame()->getScreenDimensions().x/2 + pos.x;
    float nextLevelStart = mOwner->GetGame()->getCurrentLevel() * 56 * 64;
    if(edge > nextLevelStart){
        mOwner->GetGame()->LoadLevel();
    }
    
    mOwner->GetGame()->SetCameraPos(Vector2{
        pos.x - mOwner->GetGame()->getScreenDimensions().x/2,
        0
    });

	for (auto block : mOwner->GetGame()->GetBlocks())
	{
		// Does the player collide with this block?
		if (mOwner->GetCollision()->Intersect(block->GetCollision()))
		{
			// Get player min/max and block min/max
			Vector2 playerMin = mOwner->GetCollision()->GetMin();
			Vector2 playerMax = mOwner->GetCollision()->GetMax();
			Vector2 blockMin = block->GetCollision()->GetMin();
			Vector2 blockMax = block->GetCollision()->GetMax();

			// Figure out which side we are closest to
			float dx1 = blockMin.x - playerMax.x;
			float dx2 = blockMax.x - playerMin.x;
			float dy1 = blockMin.y - playerMax.y;
			float dy2 = blockMax.y - playerMin.y;

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

			// Are we closer to top or bottom?
			if (Math::Abs(dy) < Math::Abs(dx))
			{
				pos.y += dy;
				if (dy < 0.0f)
				{
					// Landed on top
					mYSpeed = 0.0f;
					mInAir = false;
				}
				else if (mYSpeed < 0.0f)
				{
					mYSpeed = 0.0f;
				}
			}
			else
			{
				pos.x += dx;
			}

			mOwner->SetPosition(pos);
		}
	}

	mYSpeed += 2000.0f * deltaTime;
}

void PlayerMove::ProcessInput(const Uint8* keyState)
{
	if (!mSpacePressed && keyState[SDL_SCANCODE_SPACE] && !mInAir)
	{
		mYSpeed = -500.0f;
		mInAir = true;
		Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Player/Jump.wav"), 0);
	}

	mSpacePressed = keyState[SDL_SCANCODE_SPACE];
}
