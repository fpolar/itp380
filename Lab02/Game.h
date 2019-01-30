#pragma once

// TODO

#include "SDL/SDL.h"

class Game{
public:
    
    Game();
    bool Initialize();
    void ShutDown();
    void RunLoop();
    
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    
    bool runGameLoop;
    
    int prevTime;
    
    const int screenHeight = 768;
    const int screenWidth = 1024;
    
    const int wallWidth = 30;
    
    SDL_Point paddlePos;
    const int paddleWidth = 20;
    const int paddleHeight = 100;
    const float paddleVelocity = 777;
    int paddleMovement;
    
    SDL_Point ballPos;
    SDL_Point ballVelocity;
    const int ballDim = 10;
    
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    
};
