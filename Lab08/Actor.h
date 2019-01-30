#pragma once
#include <vector>
#include <SDL/SDL_stdinc.h>
#include "Math.h"
class SpriteComponent;
class MeshComponent;
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
	const Vector3& GetPosition() const { return mPosition; }
	void SetPosition(const Vector3& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }
	
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }
    
    MoveComponent* GetMoveComponent() { return mMove; }
    void SetMoveComponent(MoveComponent* move) { mMove = move; }
    CollisionComponent* GetCollisionComponent() { return mCollision; }
    void SetCollisionComponent(CollisionComponent* collision) { mCollision = collision; }
    
    Vector3 GetForward() const;
    
    const Matrix4& GetWorldTransform() const { return mWorldTransform; }

protected:
	class Game* mGame;
	// Actor's state
	State mState;
	// Transform
	Vector3 mPosition;
	float mScale;
	float mRotation;
    
    MoveComponent* mMove;
    CollisionComponent* mCollision;
    MeshComponent* mMesh;
    
    Matrix4 mWorldTransform;
};
