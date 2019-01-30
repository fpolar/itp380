#pragma once
#include "MoveComponent.h"

class BarrelMove : public MoveComponent
{
public:
	BarrelMove(class Actor* owner);
	void Update(float deltaTime) override;
protected:
	float mYSpeed = 0.0f;
};
