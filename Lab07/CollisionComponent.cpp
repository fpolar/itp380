#include "CollisionComponent.h"
#include "SpriteComponent.h"
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
    Vector2 otherMin = other->GetMin();
    Vector2 otherMax = other->GetMax();
    if(otherMax.x < GetMin().x) return false;
    if(otherMax.y < GetMin().y) return false;
    if(otherMin.x > GetMax().x) return false;
    if(otherMin.y > GetMax().y) return false;
    return true;
}

Vector2 CollisionComponent::GetMin() const
{
    return Vector2{
        mOwner->GetPosition().x - GetWidth() * mOwner->GetScale() / 2.0f,
        mOwner->GetPosition().y - GetHeight() * mOwner->GetScale() / 2.0f
    };
}

Vector2 CollisionComponent::GetMax() const
{
    return Vector2{
        mOwner->GetPosition().x + GetWidth() * mOwner->GetScale() / 2.0f,
        mOwner->GetPosition().y + GetHeight() * mOwner->GetScale() / 2.0f
    };
}

const Vector2& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

