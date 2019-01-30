#include "Block.h"
#include "SpriteComponent.h"
#include <string>
#include "Game.h"
#include <algorithm>
#include "CollisionComponent.h"

Block::Block(class Game* game)
:Actor(game)
{
	mSprite = new SpriteComponent(this);
	mCollision = new CollisionComponent(this);
	mCollision->SetSize(64.0f, 32.0f);
	
	GetGame()->GetBlocks().emplace_back(this);
}

Block::~Block()
{
    mGame->RemoveBlock(this);
}

void Block::SetBlockType(char type)
{
	std::string name = "Assets/Block";
	name += type;
	name += ".png";
	mSprite->SetTexture(GetGame()->GetTexture(name));
}

void Block::UpdateActor(float deltaTime){
    if(GetPosition().x < mGame->GetCameraPos().x - this->GetSprite()->GetTexWidth()/2) this->SetState(Actor::State::EDead);
}
