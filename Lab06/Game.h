#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);

	Mix_Chunk* GetSound(const std::string& fileName);

	void LoadLevel();

    // Lab 5 functions
    std::vector<class Block*>& GetBlocks() { return mBlocks; }
    void RemoveBlock(class Block* block);
    class Player* GetPlayer() { return mPlayer; }
    
    const Vector2& GetCameraPos() { return mCameraPos; }
    void SetCameraPos(const Vector2& cPos) { mCameraPos = cPos; }
    
    Vector2 getScreenDimensions(){return screenDim;}
    float getCurrentLevel(){return currentLevel;}
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
    
    Vector2 screenDim;
    Vector2 mCameraPos;
    
    int currentLevel = 0;
    
	// Map of textures loaded
	std::unordered_map<std::string, SDL_Texture*> mTextures;
	std::unordered_map<std::string, Mix_Chunk*> mSounds;

	// All the actors in the game
	std::vector<class Actor*> mActors;

	// All the sprite components drawn
	std::vector<class SpriteComponent*> mSprites;
	
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;

	// Lab 5 data
	std::vector<class Block*> mBlocks;
	class Player* mPlayer;
};
