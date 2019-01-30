//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "SDL/SDL_image.h"
#include <algorithm>
#include "SpriteComponent.h"
#include "AnimatedSprite.h"
#include "Actor.h"
#include "Block.h"
#include "Player.h"
#include "Coin.h"
#include "BarrelSpawner.h"
#include "Background.h"
#include <fstream>
#include <iostream>

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mIsRunning(true)
{
	
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
    
    screenDim = Vector2{1024, 768};
	mWindow = SDL_CreateWindow("ITP Game", 100, 100, screenDim.x, screenDim.y, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	LoadData();

	mTicksCount = SDL_GetTicks();
	
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	for (auto actor : mActors)
	{
		actor->ProcessInput(state);
	}
}

void Game::UpdateGame()
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();
	
	// Make copy of actor vector
	// (iterate over this in case new actors are created)
	std::vector<Actor*> copy = mActors;
	// Update all actors
	for (auto actor : copy)
	{
		actor->Update(deltaTime);
	}

	// Add any dead actors to a temp vector
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// Delete any of the dead actors (which will
	// remove them from mActors)
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderClear(mRenderer);
	
	// Draw all sprite components
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
    Actor* skyBGActor = new Actor(this);
    skyBGActor->SetPosition(Vector2{-512.0f, 0});
    Background* sky = new Background(skyBGActor, 97);
    sky->setParallax(0.25f);
    sky->AddImage(GetTexture("Assets/Background/Sky_0.png"));
    sky->AddImage(GetTexture("Assets/Background/Sky_1.png"));
    sky->AddImage(GetTexture("Assets/Background/Sky_2.png"));
    
    Actor* midBGActor = new Actor(this);
    midBGActor->SetPosition(Vector2{-512.0f, 0});
    Background* mid = new Background(midBGActor, 98);
    mid->setParallax(0.5f);
    mid->AddImage(GetTexture("Assets/Background/Mid_0.png"));
    mid->AddImage(GetTexture("Assets/Background/Mid_1.png"));
    mid->AddImage(GetTexture("Assets/Background/Mid_2.png"));
    
    Actor* foreBGActor = new Actor(this);
    foreBGActor->SetPosition(Vector2{-512.0f, 0});
    Background* fore = new Background(foreBGActor, 99);
    fore->setParallax(0.75f);
    fore->AddImage(GetTexture("Assets/Background/Fore_0.png"));
    fore->AddImage(GetTexture("Assets/Background/Fore_1.png"));
    fore->AddImage(GetTexture("Assets/Background/Fore_2.png"));
    
	LoadLevel();
}

void Game::LoadLevel()
{
    std::string nextLevel =  "Assets/Level" + std::to_string(currentLevel++%4) + ".txt";
    
    std::cout << nextLevel << std::endl;
    
	std::ifstream file(nextLevel);
	if (!file.is_open())
	{
		SDL_Log("Failed to load level: %s", nextLevel.c_str());
	}
	
	size_t row = 0;
	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);
		for (size_t col = 0; col < line.size(); col++)
		{
			Vector2 pos;
			pos.x = currentLevel * 56 * 64 + 32.0f + 64.0f * col;
			pos.y = 16.0f + 32.0f * row;
			if (line[col] != '.' &&
                line[col] != 'P' &&
                line[col] != 'O' &&
                line[col] != '*')
			{
				Block* b = new Block(this);
				b->SetPosition(pos);
				b->SetBlockType(line[col]);
			}
			else if (mPlayer == nullptr && line[col] == 'P')
			{
				mPlayer = new Player(this);
				mPlayer->SetPosition(pos);
				mPlayer->SetStartPos(pos);
            }
            else if (line[col] == 'O')
            {
                BarrelSpawner* b = new BarrelSpawner(this);
                b->SetPosition(pos);
            }
            else if (line[col] == '*')
            {
                Coin* c = new Coin(this);
                pos.y -= 16.0f;
                c->SetPosition(pos);
            }
		}
		row++;
	}
}

void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Destroy textures
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();

	// Destroy sounds
	for (auto s : mSounds)
	{
		Mix_FreeChunk(s.second);
	}
	mSounds.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// Create texture from surface
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName, tex);
	}
	return tex;
}

Mix_Chunk* Game::GetSound(const std::string& fileName)
{
	Mix_Chunk* chunk = nullptr;
	auto iter = mSounds.find(fileName);
	if (iter != mSounds.end())
	{
		chunk = iter->second;
	}
	else
	{
		chunk = Mix_LoadWAV(fileName.c_str());
		if (!chunk)
		{
			SDL_Log("Failed to load sound file %s", fileName.c_str());
			return nullptr;
		}

		mSounds.emplace(fileName, chunk);
	}
	return chunk;
}

void Game::Shutdown()
{
	UnloadData();
	Mix_CloseAudio();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	mActors.emplace_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		auto iter2 = mActors.end() - 1;
		std::iter_swap(iter, iter2);
		mActors.pop_back();
	}
}


void Game::RemoveBlock(Block* block)
{
    auto iter = std::find(mBlocks.begin(), mBlocks.end(), block);
    if (iter != mBlocks.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        auto iter2 = mBlocks.end() - 1;
        std::iter_swap(iter, iter2);
        mBlocks.pop_back();
    }
}
void Game::AddSprite(SpriteComponent* sprite)
{
	mSprites.emplace_back(sprite);
	std::sort(mSprites.begin(), mSprites.end(), [](SpriteComponent* a, SpriteComponent* b) {
		return a->GetDrawOrder() < b->GetDrawOrder();
	});
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}
