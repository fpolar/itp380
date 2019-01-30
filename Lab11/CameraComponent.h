//
//  CameraComponent.hpp
//  Game-mac
//
//  Created by Pol, Frank A. on 10/25/18.
//  Copyright © 2018 Sanjay Madhav. All rights reserved.
//

/*
 
 • Create a new Component subclass called CameraComponent. Add an override of Update
 
 
 */
#include "Component.h"

class CameraComponent: public Component{
public:
    CameraComponent(class Actor* owner);
    void Update(float deltaTime) override;
    float GetPitchSpeed(){ return mPitchSpeed; }
    void SetPitchSpeed(float p){ mPitchSpeed = p; }
private:
    float mPitchAngle;
    float mPitchSpeed;
};
