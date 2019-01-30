#pragma once

// TODO

#include "SDL/SDL.h"
#include "vector"
#include "unordered_map"
#include "string"
#include "SDL/SDL_mixer.h"

class Actor;
class Grid;
class Plane;
class SpriteComponent;
class MoveComponent;

class Game{
public:
    
    Game();
    bool Initialize();
    void ShutDown();
    void RunLoop();
    
    int GetWindowWidth(){ return screenWidth; }
    int GetWindowHeight(){ return screenHeight; }
    
    void AddActor(Actor* a);
    void RemoveActor(Actor* a);
    
    void AddPlane(Plane* a);
    void RemovePlane(Plane* p);
    std::vector<Plane*> GetPlanes(){return planes;};
    
    void AddSprite(SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);
    
    SDL_Texture* GetTexture(const char* file);
    Mix_Chunk* GetSound(const char* file);
    
    Grid* GetGrid(){ return grid; };
    void SetGrid(Grid* g){ grid = g; };
    
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    
    bool runGameLoop;
    
    int prevTime;
    
    const int screenHeight = 768;
    const int screenWidth = 1024;
    const int levelHeight = 24;
    const int levelWidth = 16;
    
    Grid* grid;
    
    std::vector<Actor*> actors;
    std::vector<Plane*> planes;
    SDL_Texture *bgTexture;
    
    std::unordered_map<std::string, Mix_Chunk*> sounds;
    std::unordered_map<std::string, SDL_Texture*> sprites;
    std::vector<SpriteComponent*> spriteComponents;
    
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    
    void LoadLevel(const char* file);
    
    void LoadData();
    void UnloadData();
    
};
