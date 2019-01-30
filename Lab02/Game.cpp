//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include <iostream>

// TODO

Game::Game(){
}

bool Game::Initialize(){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 0;
    }
    
    window = SDL_CreateWindow(
                              "Pong 3: The Dark Pong Rises",                  // window title
                                          0,                                 // initial x position
                                          0,                                 // initial y position
                                          screenWidth,                               // width, in pixels
                                          screenHeight,                               // height, in pixels
                                          SDL_WINDOW_OPENGL                  // flags - see below
                                          );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    runGameLoop = true;
    prevTime = SDL_GetTicks();
    paddlePos = {wallWidth, screenHeight/2};
    ballPos = {screenWidth/2, screenHeight/2};
    
    ballVelocity = {400, 200};
    
    return true;
}

void Game::ShutDown(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::RunLoop(){
    while(runGameLoop){
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput(){
    
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT){
            runGameLoop = false;
        }
    }
    
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_ESCAPE]){
        runGameLoop = false;
    }
    
    paddleMovement = 0;
    
    if(state[SDL_SCANCODE_UP]){
        paddleMovement = 1;
    }
    if(state[SDL_SCANCODE_DOWN]){
        paddleMovement = 2;
    }
}
void Game::UpdateGame(){
    int currTime = SDL_GetTicks();
    float deltaTime = currTime - prevTime;
    while(deltaTime<16){
        currTime = SDL_GetTicks();
        deltaTime = currTime - prevTime;
    }
    prevTime = currTime;
    deltaTime > 50 ? deltaTime=.05 : deltaTime=deltaTime/1000;
    
    //paddle movement
    if(paddleMovement == 1){
        paddlePos.y-=paddleVelocity*deltaTime;
    }
    if(paddleMovement == 2){
        paddlePos.y+=paddleVelocity*deltaTime;
    }
    
    if(paddlePos.y > screenHeight-wallWidth-paddleHeight/2){
        paddlePos.y =screenHeight-wallWidth-paddleHeight/2;
    }
    if(paddlePos.y < wallWidth+paddleHeight/2){
        paddlePos.y = wallWidth+paddleHeight/2;
    }
    
    //ball velocity to position calc
    ballPos.x -= ballVelocity.x*deltaTime;
    ballPos.y += ballVelocity.y*deltaTime;
    
    //losing scenario
    if(ballPos.x<0){
        runGameLoop = false;
    }
    
    //ball hits paddle
    if(ballPos.x <= paddlePos.x+paddleWidth/2 &&
       ballPos.y <= paddlePos.y + paddleHeight/2 &&
       ballPos.y >= paddlePos.y - paddleHeight/2){
        ballPos.x = paddlePos.x + paddleWidth;
        ballVelocity.x *= -1;
    }
    
    //ball hits back wall
    if(ballPos.x >= screenWidth-wallWidth){
        ballPos.x = screenWidth-wallWidth;
        ballVelocity.x *= -1;
    }
    
    //ball hits top wall
    if(ballPos.y <= wallWidth){
        ballPos.y = wallWidth;
        ballVelocity.y *= -1;
    }
    
    //ball hits bottom wall
    if(ballPos.y >= screenHeight-wallWidth){
        ballPos.y = screenHeight-wallWidth;
        ballVelocity.y *= -1;
    }
}
void Game::GenerateOutput(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect tempRect = {0,0,screenWidth, wallWidth};
    SDL_RenderFillRect(renderer, &tempRect);
    tempRect = {screenWidth-wallWidth, 0, wallWidth, screenHeight};
    SDL_RenderFillRect(renderer, &tempRect);
    tempRect = {0, screenHeight-wallWidth, screenWidth, screenHeight};
    SDL_RenderFillRect(renderer, &tempRect);
    
    SDL_Rect paddleRect = {paddlePos.x - paddleWidth/2, paddlePos.y - paddleHeight/2, paddleWidth, paddleHeight};
    SDL_RenderFillRect(renderer, &paddleRect);
    
    SDL_Rect ballRect = {ballPos.x, ballPos.y, ballDim, ballDim};
    SDL_RenderFillRect(renderer, &ballRect);

    SDL_RenderPresent(renderer);
}
