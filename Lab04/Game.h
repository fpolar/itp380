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
class Paddle;
class Ball;
class Block;

class Game{
public:
    
    Game();
    bool Initialize();
    void ShutDown();
    void RunLoop();
    
    int GetWindowWidth(){ return screenWidth; }
    int GetWindowHeight(){ return screenHeight; }
    int GetWallWidth(){ return wallWidth; }
    
    Paddle* GetPaddle() { return paddle; }
    Ball* getBall() { return ball; }
    
    void AddActor(Actor* a);
    void RemoveActor(Actor* a);
    
    void AddBlock(Block* a);
    void RemoveBlock(Block* a);
    std::vector<Block*> getBlocks(){ return blocks; }
    
    void AddSprite(SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);
    
    SDL_Texture* getTexture(const char* file);
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    
    Paddle* paddle;
    Ball* ball;
    
    bool runGameLoop;
    
    int prevTime;
    
    const int screenHeight = 768;
    const int screenWidth = 1024;
    const int wallWidth  = 32;
    
    std::vector<Actor*> actors;
    std::vector<Block*> blocks;
    SDL_Texture *bgTexture;
    
    std::unordered_map<std::string, SDL_Texture*> sprites;
    std::vector<SpriteComponent*> spriteComponents;
    
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    
    void LoadLevel(const char* file);
    
    void LoadData();
    void UnloadData();
    
};
