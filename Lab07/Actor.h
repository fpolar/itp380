#pragma once
#include <vector>
#include <SDL/SDL_stdinc.h>
#include "Math.h"
class SpriteComponent;
class MoveComponent;
class CollisionComponent;

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
	
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }
    
    SpriteComponent* GetSprite() { return mSprite; }
    void SetSprite(SpriteComponent* sprite) { mSprite = sprite; }
    MoveComponent* GetMoveComponent() { return mMove; }
    void SetMoveComponent(MoveComponent* move) { mMove = move; }
    CollisionComponent* GetCollisionComponent() { return mCollision; }
    void SetCollisionComponent(CollisionComponent* collision) { mCollision = collision; }
    
    Vector2 GetForward();

protected:
	class Game* mGame;
	// Actor's state
	State mState;
	// Transform
	Vector2 mPosition;
	float mScale;
	float mRotation;
    
    SpriteComponent* mSprite;
    MoveComponent* mMove;
    CollisionComponent* mCollision;
    
};
