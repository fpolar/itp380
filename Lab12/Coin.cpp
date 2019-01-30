#include "Coin.h"
#include "CollisionComponent.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Game.h"
#include "HUD.h"
#include "Renderer.h"
#include "Player.h"

Coin::Coin(Game* game):Actor(game)
{
	mCollision = new CollisionComponent(this);
	mCollision->SetSize(100.0f,100.0f,100.0f);
	mMesh = new MeshComponent(this);
	mMesh->SetMesh(game->GetRenderer()->GetMesh("Assets/Coin.gpmesh"));
}

void Coin::UpdateActor(float deltaTime) {
	if (mCollision->Intersect(mGame->GetPlayer()->GetCollisionComponent())) {
		Mix_PlayChannel(-1, mGame->GetSound("Assets/Sounds/Coin.wav"), 0);
		mGame->GetHUD()->IncrementCoinCointer();
		SetState(EDead);
		return;
	}
	mRotation += Math::Pi*deltaTime;
}
