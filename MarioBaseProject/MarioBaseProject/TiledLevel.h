#pragma once
#include "GameScreen.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "TileInformation.h"

class TiledLevel : public GameScreen
{
public:
	TiledLevel(SDL_Renderer* renderer);
	~TiledLevel();

	bool LoadMap(const std::string& fileName);

	void GenerateObjects();

	void ClearMap();

	int GetValueAtTile(int row, int column) {
		if (row < mLevelHeight && column < mLevelWidth && row >= 0 && column >= 0) {
			return mMap.at(row).at(column);
		}
		else
		{
			return -1;
		}
	}

	void ChangeTileAt(int row, int column, int newValue);

	int GetCalculatedLevelWidth() { return mLevelWidth * TILE_WIDTH; }
	int GetCalculatedLevelHeight() { return mLevelHeight * TILE_HEIGHT; }

	virtual void Render() override;
	virtual void Update(float deltaTime, SDL_Event event) override;

private:
	int mLevelWidth, mLevelHeight;

	std::vector<std::vector<int>> mMap;
	std::vector<std::vector<class Tile*>> mTileMap;
};

