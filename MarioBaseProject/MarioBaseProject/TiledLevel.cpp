#include "TiledLevel.h"

#include "Tile.h"
#include <vector>

TiledLevel::TiledLevel(SDL_Renderer* renderer) : GameScreen(renderer)
{

}

TiledLevel::~TiledLevel()
{

}

bool TiledLevel::LoadMap(const std::string& fileName)
{
	std::ifstream mapFile;
	mapFile.open(fileName);
	if (mapFile.good()) {
		mLevelWidth = 0;
		mLevelHeight = 0;

		while (mapFile.good())
		{
			std::string line;
			getline(mapFile, line, '\n');
			std::istringstream iss(line);
			std::string token;
			std::vector<int>row;
			while (std::getline(iss, token, ',')) 
			{
				row.push_back(std::stoi(token));
			}

			mMap.push_back(row);
			row.clear();
		}
		mLevelHeight = mMap.size() - 1;
		mLevelWidth = mMap[mLevelHeight - 1].size();

		GenerateObjects();
		return true;
	}
	else
	{
		printf("Failed to load level: %s", fileName.c_str());
	}
}

void TiledLevel::GenerateObjects()
{
	int type = 0;

	for (int row = 0; row < mLevelHeight; row++) {
		std::vector<Tile*> tileRow;
		for (int column = 0; column < mLevelWidth; column++) {
			type = mMap.at(row).at(column);
			if (type == -1) {
				SDL_Rect* blankSrc = new SDL_Rect{ 160,0,TILE_WIDTH,TILE_HEIGHT };
				SDL_Rect* blankDest = new SDL_Rect{ column * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

				Tile* blankTile = new Tile(mRenderer, blankSrc, blankDest, -1);

				tileRow.push_back(blankTile);
			}
			else if (type == 0) {
				SDL_Rect* brickSrc = new SDL_Rect{ 0,0,TILE_WIDTH,TILE_HEIGHT };
				SDL_Rect* brickDest = new SDL_Rect{ column * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

				Tile* brick = new Tile(mRenderer, brickSrc, brickDest, 0);
				tileRow.push_back(brick);
			}
			else if (type == 1) {
				SDL_Rect* brickSrc = new SDL_Rect{ 32,0,TILE_WIDTH, TILE_HEIGHT };
				SDL_Rect* brickDest = new SDL_Rect{ column * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

				Tile* brick = new Tile(mRenderer, brickSrc, brickDest, -1);
				tileRow.push_back(brick);
			}
			else if (type == 2) {
				SDL_Rect* brickSrc = new SDL_Rect{ 0,0,TILE_WIDTH,TILE_HEIGHT };
				SDL_Rect* brickDest = new SDL_Rect{ column * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

				Tile* brick = new Tile(mRenderer, brickSrc, brickDest, 0);
				tileRow.push_back(brick);
			}
			//else if (type == 3) {
			//	SDL_Rect* blankSrc = new SDL_Rect{ 160,0,TILE_WIDTH,TILE_HEIGHT };
			//	SDL_Rect* blankDest = new SDL_Rect{ column * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

			//	Tile* blankTile = new Tile(mRenderer, blankSrc, blankDest, -1);

			//	tileRow.push_back(blankTile);

			//	
			//}
			//else if (type == 4) {
			//	SDL_Rect* goalSrc = new SDL_Rect{ 128,0,TILE_WIDTH,TILE_HEIGHT };
			//	SDL_Rect* goalDest = new SDL_Rect{ column * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

			//	LevelGoal* goal = new LevelGoal(mOwner->GetGame(), goalSrc, goalDest);
			//	mOwner->GetGame()->AddLevelGoal(goal);
			//	tileRow.push_back(goal);
			//}
			else if (type == 32) {
				SDL_Rect* goldBrickSrc = new SDL_Rect{ 0,32,TILE_WIDTH,TILE_HEIGHT };
				SDL_Rect* goldBrickDest = new SDL_Rect{ column * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

				Tile* brick = new Tile(mRenderer, goldBrickSrc, goldBrickDest, 2);
				tileRow.push_back(brick);
			}
			//else if (type == 64) {
			//	SDL_Rect* coinSrc = new SDL_Rect{ 0,64,TILE_WIDTH,TILE_HEIGHT };
			//	SDL_Rect* coinDest = new SDL_Rect{ column * TILE_WIDTH, (row * TILE_HEIGHT), TILE_WIDTH, TILE_HEIGHT };

			//	Coin* coin = new Coin(mOwner->GetGame(), coinSrc, coinDest);
			//	mOwner->GetGame()->AddCoin(coin);
			//	tileRow.push_back(coin);
			//}
			else {

			}
		}
		mTileMap.push_back(tileRow);
		tileRow.clear();
	}
}

void TiledLevel::ClearMap()
{
	mMap.clear();
}

void TiledLevel::ChangeTileAt(int row, int column, int newValue)
{
	if (row < mLevelHeight && column < mLevelWidth && row >= 0 && column >= 0) {
		mMap.at(row).at(column) = newValue;
	}
}

void TiledLevel::Render()
{
	for (unsigned int row = 0; row < mTileMap.size(); row++) {
		for (unsigned int column = 0; column < mTileMap[row].size(); column++) {
			mTileMap.at(row).at(column)->Render(mRenderer);
		}
	}
}

void TiledLevel::Update(float deltaTime, SDL_Event event)
{

}

