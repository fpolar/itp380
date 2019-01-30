//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Random.h"
#include <iostream>
#include <algorithm>
#include <SDL/SDL_image.h>

// TODO


Game::Game(){
}

bool Game::Initialize(){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 0;
    }
    
    Random::Init(); 
    
    window = SDL_CreateWindow(
                              "See Ya Later Space Cowboy",                  // window title
                                          0,                                 // initial x position
                                          0,                                 // initial y position
                                          screenWidth,                               // width, in pixels
                                          screenHeight,                               // height, in pixels
                                          SDL_WINDOW_OPENGL                  // flags - see below
                                          );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    runGameLoop = true;
    prevTime = SDL_GetTicks();
    
    LoadData();
    
    IMG_Init(IMG_INIT_PNG);
    
    return true;
}

void Game::ShutDown(){
    UnloadData();
    IMG_Quit();
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
    
    std::vector<Actor*> actorsCopy = actors;
    for(int i=0;i<actorsCopy.size(); i++){
        actorsCopy[i]->ProcessInput(state);
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
    
    std::vector<Actor*> actorsCopy = actors;
    std::vector<Actor*> deadActors;
    for(int i=0;i<actorsCopy.size(); i++){
        actorsCopy[i]->Update(deltaTime);
    }
    for(int i=0;i<actorsCopy.size(); i++){
        if(actorsCopy[i]->GetState() == Actor::State::EDead){
            deadActors.push_back(actorsCopy[i]);
        }
    }
    for(int i=0;i<deadActors.size(); i++){
        delete deadActors[i];
    }
    
    
}
void Game::GenerateOutput(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    for(int i=0;i<spriteComponents.size(); i++){
        spriteComponents[i]->Draw(renderer);
    }

    SDL_RenderPresent(renderer);
    
}

void Game::AddActor(Actor* a){
    actors.push_back(a);
}

void Game::RemoveActor(Actor* a){
    actors.erase(std::find(actors.begin(), actors.end(), a));
}

void Game::AddAsteroid(Asteroid* a){
    asteroids.push_back(a);
}

void Game::RemoveAsteroid(Asteroid* a){
    asteroids.erase(std::find(asteroids.begin(), asteroids.end(), a));
}

void Game::AddSprite(SpriteComponent *sprite){
    spriteComponents.push_back(sprite);
    std::sort(spriteComponents.begin(), spriteComponents.end(),
              [](SpriteComponent* a, SpriteComponent* b) {
                  
                  return a->GetDrawOrder() < b->GetDrawOrder();
              });
}

void Game::RemoveSprite(SpriteComponent *sprite){
    spriteComponents.erase(std::find(spriteComponents.begin(), spriteComponents.end(), sprite));
}

void Game::LoadData(){
    
    Actor* stars = new Actor(this);
    SpriteComponent* starsSprite = new SpriteComponent(stars, 50);
    starsSprite->SetTexture(getTexture("Assets/Stars.png"));
    stars->SetSprite(starsSprite);
    stars->SetPosition(Vector2{512, 384});
    
    Ship* ship = new Ship(this);
    ship->SetPosition(Vector2{static_cast<float>(screenWidth/2), static_cast<float>(screenHeight/2)});
    
    for(int i=0;i<10;i++){
        new Asteroid(this);
    }
    
}

void Game::UnloadData(){
    for(Actor* actor: actors){
        delete actor;
    }
    SDL_DestroyTexture(bgTexture);
    for(std::pair<std::string, SDL_Texture*> sprite: sprites){
        SDL_DestroyTexture(sprite.second);
    }
    sprites.clear();
}

SDL_Texture* Game::getTexture(const char *file){
    std::string temp(file);
    if(sprites.find(temp) == sprites.end()){
        SDL_Surface *image = IMG_Load(file);
        sprites[file] = SDL_CreateTextureFromSurface(renderer, image);
    }
    return sprites[file];
}
