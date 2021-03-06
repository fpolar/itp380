#pragma once
#include <vector>
#include <SDL/SDL_stdinc.h>
#include "Math.h"
class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};
	
	Actor(class Game* game);
	virtual ~Actor();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);
	// ProcessInput function called from Game (not overridable)
	void ProcessInput(const Uint8* keyState);
	// Any actor-specific update code (overridable)
	virtual void ActorInput(const Uint8* keyState);

	// Getters/setters
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }
	
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }

	class SpriteComponent* GetSprite() { return mSprite; }
	class MoveComponent* GetMove() { return mMove; }
	class CollisionComponent* GetCollision() { return mCollision; }
protected:
	class Game* mGame;
	// Actor's state
	State mState;

	// Transform
	Vector2 mPosition;
	float mScale;
	float mRotation;
	
	// Components
	class SpriteComponent* mSprite;
	class MoveComponent* mMove;
	class CollisionComponent* mCollision;
};
