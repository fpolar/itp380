//
//  CameraComponent.cpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/25/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//
#include "Game.h"
#include "Actor.h"
#include "Renderer.h"
#include "CameraComponent.h"

CameraComponent::CameraComponent(Actor* owner):Component(owner){
    mPitchAngle = 0.0f;
    mPitchSpeed = 0.0f;
}

void CameraComponent::Update(float deltaTime){
    
    /*
     The target position computation now changes
     o Make two rotation matrices: one for pitch and one for yaw (think about which of
     the X, Y, Z rotations each corresponds to)
     ▪ The pitch angle is mPitchAngle
     ▪ The yaw angle is the owner’s rotation
     o Multiply these rotation matrices (pitch * yaw) to get a combined rotation matrix
     o Use Vector3::Transform to transform <1, 0, 0> by the combined matrix – note the
     function returns the transformed vector
     o The vector from the previous step is your camera’s forward vector. Use this
     (instead of the owner’s forward) to calculate the target position you pass to
     CreateLookAt
     */
    
    Matrix4 pitchMatrix = Matrix4::CreateRotationY(mPitchAngle);
    Matrix4 yawMatrix = Matrix4::CreateRotationZ(mOwner->GetRotation());
    
    Matrix4 rotationMatrix = pitchMatrix * yawMatrix;
    
    Vector3 forward = Vector3::Transform(Vector3{1, 0, 0}, rotationMatrix);
    
    Matrix4 viewMatrix = Matrix4::CreateLookAt(
                                               mOwner->GetPosition(),
                                               mOwner->GetPosition() + forward,
                                               Vector3{0, 0, 1}
                                               );
    
    mOwner->GetGame()->GetRenderer()->SetViewMatrix(viewMatrix);
    
    mPitchAngle += mPitchSpeed*deltaTime;
    if(mPitchAngle < -Math::Pi/4){
        mPitchAngle = -Math::Pi/4;
    }
    if(mPitchAngle > Math::Pi/4){
        mPitchAngle = Math::Pi/4;
    }
}
