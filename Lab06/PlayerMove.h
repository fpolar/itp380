#pragma once
#include "MoveComponent.h"

class PlayerMove : public MoveComponent
{
public:
	PlayerMove(class Actor* owner);
	void Update(float deltaTime) override;
	void ProcessInput(const Uint8* keyState) override;
protected:
	float mYSpeed = 0.0f;
	bool mSpacePressed = false;
	float mAirtime = 0.0f;
	bool mInAir = false;
};
