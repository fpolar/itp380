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
#include "CollisionComponent.h"
#include "Random.h"
#include "Grid.h"
#include "Tile.h"
#include <iostream>
#include <algorithm>
#include <SDL/SDL_image.h>
#include <fstream>
#include "SDL/SDL_mixer.h"

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
                              "Bloons without the monkeys or bloons",                  // window title
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
    Mix_CloseAudio();
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
    SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255);
    SDL_RenderClear(renderer);
    
    
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

void Game::AddPlane(Plane* p){
    planes.push_back(p);
}

void Game::RemovePlane(Plane* p){
    planes.erase(std::find(planes.begin(), planes.end(), p));
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
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    grid = new Grid(this);
//    Actor* bg = new Actor(this);
//    SpriteComponent* bg_sc = new SpriteComponent(bg);
//    bg_sc->SetTexture(getTexture("Assets/Background.png"));
//    bg->SetPosition(Vector2{screenWidth/2.0f, screenHeight/2.0f});
    
    std::cout << grid->TryFindPath() << std::endl;
    grid->UpdatePathTiles();
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
    for(std::pair<std::string, Mix_Chunk*> sound: sounds){
        Mix_FreeChunk(sound.second);
    }
    sounds.clear();
}

SDL_Texture* Game::GetTexture(const char *file){
    std::string temp(file);
    if(sprites.find(temp) == sprites.end()){
        SDL_Surface *image = IMG_Load(file);
        sprites[file] = SDL_CreateTextureFromSurface(renderer, image);
    }
    return sprites[file];
}

Mix_Chunk* Game::GetSound(const char *file){
    if(sounds.find(file) == sounds.end()){
        sounds[file] = Mix_LoadWAV(file);
    }
    return sounds[file];
    
}
