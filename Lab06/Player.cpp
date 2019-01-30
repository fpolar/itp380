#include "Player.h"
#include "SpriteComponent.h"
#include "PlayerMove.h"
#include "Game.h"
#include "CollisionComponent.h"

Player::Player(class Game* game)
:Actor(game)
{
    mSprite = new AnimatedSprite(this, 100);
    mSprite->AddImage(GetGame()->GetTexture("Assets/Player/Run1.png"));
    mSprite->AddImage(GetGame()->GetTexture("Assets/Player/Run2.png"));
    mSprite->AddImage(GetGame()->GetTexture("Assets/Player/Run3.png"));
    mSprite->AddImage(GetGame()->GetTexture("Assets/Player/Run4.png"));
    mSprite->AddImage(GetGame()->GetTexture("Assets/Player/Run5.png"));
    mSprite->AddImage(GetGame()->GetTexture("Assets/Player/Run6.png"));
    mSprite->AddImage(GetGame()->GetTexture("Assets/Player/Run7.png"));
    mSprite->AddImage(GetGame()->GetTexture("Assets/Player/Run8.png"));
    mSprite->AddImage(GetGame()->GetTexture("Assets/Player/Run9.png"));
    mSprite->AddImage(GetGame()->GetTexture("Assets/Player/Run10.png"));
    Actor::mSprite = mSprite; 
	mMove = new PlayerMove(this);
	
	mCollision = new CollisionComponent(this);
	mCollision->SetSize(20.0f, 64.0f);
}
