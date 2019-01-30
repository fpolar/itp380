#include "Grid.h"
#include "Tower.h"
#include "Tile.h"
#include "Plane.h"
#include <SDL/SDL.h>
#include <algorithm>
#include <iostream>

Grid::Grid(class Game* game)
	:Actor(game)
	,mSelectedTile(nullptr)
{
	// 7 rows, 16 columns
	mTiles.resize(NumRows);
	for (size_t i = 0; i < mTiles.size(); i++)
	{
		mTiles[i].resize(NumCols);
	}
	
	// Create tiles
	for (size_t i = 0; i < NumRows; i++)
	{
		for (size_t j = 0; j < NumCols; j++)
		{
			mTiles[i][j] = new Tile(GetGame());
			mTiles[i][j]->SetPosition(Vector2(TileSize/2.0f + j * TileSize, StartY + i * TileSize));
		}
	}
	
	// Set start/end tiles
	GetStartTile()->SetTileState(Tile::EStart);
	GetEndTile()->SetTileState(Tile::EBase);
	
	// Set up adjacency lists
	for (size_t i = 0; i < NumRows; i++)
	{
		for (size_t j = 0; j < NumCols; j++)
		{
			if (i > 0)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i-1][j]);
			}
			if (i < NumRows - 1)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i+1][j]);
			}
			if (j > 0)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i][j-1]);
			}
			if (j < NumCols - 1)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i][j+1]);
			}
		}
	}
}

void Grid::SelectTile(size_t row, size_t col)
{
	// Make sure it's a valid selection
	Tile::TileState tstate = mTiles[row][col]->GetTileState();
	if (tstate != Tile::EStart && tstate != Tile::EBase)
	{
		// Deselect previous one
		if (mSelectedTile)
		{
			mSelectedTile->ToggleSelect();
		}
		mSelectedTile = mTiles[row][col];
		mSelectedTile->ToggleSelect();
	}
}

Tile* Grid::GetStartTile()
{
	return mTiles[3][0];
}

Tile* Grid::GetEndTile()
{
	return mTiles[3][15];
}

void Grid::ActorInput(const Uint8 * keyState)
{
	// Process mouse click to select a tile
	int x, y;
	Uint32 buttons = SDL_GetMouseState(&x, &y);
	if (SDL_BUTTON(buttons) & SDL_BUTTON_LEFT)
	{
		// Calculate the x/y indices into the grid
		y -= static_cast<int>(StartY - TileSize / 2);
		if (y >= 0)
		{
			x /= static_cast<int>(TileSize);
			y /= static_cast<int>(TileSize);
			if (x >= 0 && x < static_cast<int>(NumCols) && y >= 0 && y < static_cast<int>(NumRows))
			{
				SelectTile(y, x);
			}
		}
	}
    
    if (!mSpacePressed && keyState[SDL_SCANCODE_SPACE] && mSelectedTile != nullptr){
        mNeedToBuild = true;
    }
    
    mSpacePressed = keyState[SDL_SCANCODE_SPACE];
}

void Grid::UpdateActor(float deltaTime)
{
    if(mNeedToBuild){
        BuildTower(mSelectedTile);
        mNeedToBuild = false;
    }
    
    timer -= deltaTime;
    if(timer <= 0){
        timer = cooldown;
        Plane* p = new Plane(mGame);
    }
}

bool Grid::TileFComp(const Tile* t1,  const Tile* t2){ return t1->f > t2->f; }

bool Grid::TryFindPath(){
    for(std::vector<Tile*> tList: mTiles){
        for(Tile* t: tList){
            t->mInClosedSet = false;
            t->g = 0.0f;
        }
    }
    
    std::vector<Tile*> openSet;
    Tile* currentTile = GetEndTile();
    currentTile->mInClosedSet = true;
    
    while(currentTile != GetStartTile()){
        std::cout << currentTile->GetPosition().x << std::endl;
        
        for(Tile* adjTile: currentTile->mAdjacent){
            if(adjTile->mInClosedSet){
                continue;
            } else if(std::find(openSet.begin(), openSet.end(), adjTile) != openSet.end()){
                float gTemp = TileSize + currentTile->g;
                if(gTemp < adjTile->g){
                    adjTile->mParent = currentTile;
                    adjTile->g = gTemp;
                    adjTile->f = adjTile->g + adjTile->h;
                }
            } else {
                adjTile->mParent = currentTile;
                adjTile->h = (adjTile->GetPosition() - GetEndTile()->GetPosition()).Length();
                adjTile->g = TileSize + currentTile->g;
                adjTile->f = adjTile->h + adjTile->g;
                if(!adjTile->mBlocked){
                    openSet.push_back(adjTile);
                }
            }
        }
        
        if(openSet.empty()){
            return false;
        }
        
        std::sort(openSet.begin(), openSet.end(), Grid::TileFComp);
        currentTile = openSet[openSet.size()-1];
        currentTile->mInClosedSet = true;
        openSet.pop_back();
    }
    
    return true;
}

void Grid::UpdatePathTiles(){
    for(std::vector<Tile*> tList: mTiles){
        for(Tile* t: tList){
            if(t != GetStartTile() && t != GetEndTile()){
                t->SetTileState(Tile::EDefault);
            }
        }
    }
    
    Tile* currentTile = GetStartTile()->mParent;
    while(currentTile != GetEndTile()){
        currentTile->SetTileState(Tile::EPath);
        currentTile = currentTile->mParent;
    }
}

void Grid::BuildTower(Tile *t){
    if(t->mBlocked){
        return;
    }
    t->mBlocked = true;
    if(TryFindPath()){
        UpdatePathTiles();
        Tower* tower = new Tower(mGame);
        tower->SetPosition(t->GetPosition());
    }else{
        t->mBlocked = false;
    }
}
