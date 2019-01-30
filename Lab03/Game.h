#pragma once

// TODO

#include "SDL/SDL.h"
#include "vector"
#include "unordered_map"
#include "string"

class Actor;
class Asteroid;
class SpriteComponent;
class MoveComponent;

class Game{
public:
    
    Game();
    bool Initialize();
    void ShutDown();
    void RunLoop();
    
    int getWindowWidth(){ return screenWidth; }
    int getWindowHeight(){ return screenHeight; }
    
    void AddActor(Actor* a);
    void RemoveActor(Actor* a);
    
    void AddAsteroid(Asteroid* a);
    void RemoveAsteroid(Asteroid* a);
    std::vector<Asteroid*> getAsteroids(){ return asteroids; }
    
    void AddSprite(SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);
    
    SDL_Texture* getTexture(const char* file);
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    
    bool runGameLoop;
    
    int prevTime;
    
    const int screenHeight = 768;
    const int screenWidth = 1024;
    
    std::vector<Actor*> actors;
    std::vector<Asteroid*> asteroids;
    SDL_Texture *bgTexture;
    
    std::unordered_map<std::string, SDL_Texture*> sprites;
    std::vector<SpriteComponent*> spriteComponents;
    
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    
    void LoadData();
    void UnloadData();
    
};
