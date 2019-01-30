//
//  Arrow.cpp
//  Game-mac
//
//  Created by ITP on 11/15/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

#include "Arrow.h"
#include "Game.h"
#include "Player.h"
#include "Checkpoint.h"
#include "MeshComponent.h"
#include "CollisionComponent.h"
#include "Renderer.h"

Arrow::Arrow(Game* game):Actor(game){
    mMesh = new MeshComponent(this);
    mMesh->SetMesh(game->GetRenderer()->GetMesh("Assets/Arrow.gpmesh"));
    SetScale(0.15f);
}

void Arrow::UpdateActor(float deltaTime){
//    Make a vector from the player position to the active checkpoint, and normalize it
//    o Use the dot product/cross product between <1, 0, 0> and the player-to-checkpoint
//    vector to compute the angle of rotation and the axis of rotation
//    o Make sure you handle the case where the cross product length is near zero
//    o Once you have an axis/angle, use the Quaternion constructor that takes in a
//    Vector3 (for the axis) and a float (for the angle), and set mQuat to that!
//    o If the current active Checkpoint* is null, just set mQuat to Quaternion::Identity
    
    if(mGame->CurrentCheckpoint() == nullptr){
        mQuat = Quaternion::Identity;
        mPosition = mGame->GetRenderer()->Unproject(Vector3(0.0f, 250.0f, 0.1f));
        return;
    }
    
    Vector3 dir = mGame->CurrentCheckpoint()->GetPosition() - mGame->GetPlayer()->GetPosition();
    dir.Normalize();
    
    Vector3 axis = Vector3::Cross(Vector3{1, 0, 0} , dir);
    axis.Normalize();
    
    if(Math::NearZero(axis.Length())){
        mQuat = Quaternion::Identity;
        mPosition = mGame->GetRenderer()->Unproject(Vector3(0.0f, 250.0f, 0.1f));
        return;
    }
    
    float angle =  acos(Vector3::Dot(Vector3{1, 0, 0}, dir));
    mQuat = Quaternion(axis, angle);
    
    mPosition = mGame->GetRenderer()->Unproject(Vector3(0.0f, 250.0f, 0.1f));
}
