#include "CollisionComponent.h"
#include "Actor.h"

CollisionComponent::CollisionComponent(class Actor* owner)
:Component(owner)
,mWidth(0.0f)
,mHeight(0.0f)
{
	
}

CollisionComponent::~CollisionComponent()
{
	
}

bool CollisionComponent::Intersect(const CollisionComponent* other)
{
	Vector2 aMin = GetMin();
	Vector2 aMax = GetMax();
	Vector2 bMin = other->GetMin();
	Vector2 bMax = other->GetMax();

	bool no = aMax.x < bMin.x ||
		aMax.y < bMin.y ||
		bMax.x < aMin.x ||
		bMax.y < aMin.y;

	return !no;
}

Vector2 CollisionComponent::GetMin() const
{
	Vector2 v = mOwner->GetPosition();
	v.x -= mWidth * mOwner->GetScale() / 2.0f;
	v.y -= mHeight * mOwner->GetScale() / 2.0f;
	return v;
}

Vector2 CollisionComponent::GetMax() const
{
	Vector2 v = mOwner->GetPosition();
	v.x += mWidth * mOwner->GetScale() / 2.0f;
	v.y += mHeight * mOwner->GetScale() / 2.0f;
	return v;
}

const Vector2& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

