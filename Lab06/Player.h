#pragma once
#include "Actor.h"
#include "AnimatedSprite.h"
class Player : public Actor
{
public:
	Player(class Game* game);
	void SetStartPos(const Vector2& pos) { mStartPos = pos; }
	const Vector2& GetStartPos() const { return mStartPos; }
private:
	Vector2 mStartPos;
    AnimatedSprite* mSprite;
};
