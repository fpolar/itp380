#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <unordered_map>
#include <string>
#include <queue>
#include <vector>
#include "Math.h"

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
    
    class Player* GetPlayer(){ return player; }
    void SetPlayer(class Player* p){ player = p;}

	void SetNextLevel(std::string s) { mNextLevel = s; }

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);
    
    void AddBlock(class Block* block);
    void RemoveBlock(class Block* block);
    std::vector<class Block*> GetBlocks(){ return mBlocks; }
    
    void PopCheckpoint();
    void PushCheckpoint(class Checkpoint* c);
    class Checkpoint* CurrentCheckpoint(){
        if( mCheckpoints.empty() ){
            return nullptr;
        }
        return mCheckpoints.front();
    }

	Mix_Chunk* GetSound(const std::string& fileName);

	class HUD* GetHUD() { return mHUD; }

	void LoadLevel(const std::string& fileName);

	void LoadNextLevel();

	class Renderer* GetRenderer() {	return mRenderer; }
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	// Map of textures loaded
	std::unordered_map<std::string, SDL_Texture*> mTextures;
	std::unordered_map<std::string, Mix_Chunk*> mSounds;

	// All the actors in the game
	std::vector<class Actor*> mActors;
    
    std::vector<class Block*> mBlocks;
    
    std::queue<class Checkpoint*> mCheckpoints;
    
    class Player* player;
	class HUD* mHUD;
    class Renderer* mRenderer;

	Uint32 mTicksCount;
	bool mIsRunning;
    
    const int screenHeight = 768;
    const int screenWidth = 1024;

	std::string mNextLevel = "";
};
