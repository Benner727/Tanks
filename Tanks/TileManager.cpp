#include "TileManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>

TileManager* TileManager::sInstance = nullptr;

TileManager* TileManager::Instance()
{
	if (sInstance == nullptr)
		sInstance = new TileManager();

	return sInstance;
}

void TileManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

TileManager::TileManager()
{
	Pos(VEC2_ZERO);

	std::vector<std::vector<int>> tiles;
	std::vector<std::vector<float>> objects;

	ReadMap("Assets/Map/tilemap.txt", tiles);
	ReadObjects("Assets/Map/objectmap.txt", objects);

	LoadMap(tiles, objects);
}


TileManager::~TileManager()
{
	for (int i = 0; i < mTiles.size(); i++)
	{
		for (int j = 0; j < mTiles[i].size(); j++)
		{
			delete mTiles[i][j];
			mTiles[i][j] = nullptr;
		}
	}

	mTiles.clear();

	for (int i = 0; i < mObjects.size(); i++)
	{
		delete mObjects[i];
		mObjects[i] = nullptr;
	}

	mObjects.clear();
}

void TileManager::ReadMap(std::string filePath, std::vector<std::vector<int>>& fields)
{
	filePath = SDL_GetBasePath() + filePath;
	std::ifstream infile(filePath);

	if (infile)
	{
		std::string line;

		while (std::getline(infile, line))
		{
			std::stringstream sep(line);
			std::string field;
			fields.push_back(std::vector<int>());

			while (std::getline(sep, field, ','))
			{
				fields.back().push_back(37 - std::stoi(field));
			}
		}
	}
	else
		std::cerr << "Unable to open file path: " << filePath << "!" << std::endl;
}

void TileManager::ReadObjects(std::string filePath, std::vector<std::vector<float>> &fields)
{
	filePath = SDL_GetBasePath() + filePath;
	std::ifstream infile(filePath);

	if (infile)
	{
		std::string line;

		while (std::getline(infile, line))
		{
			std::stringstream sep(line);
			std::string field;
			fields.push_back(std::vector<float>());

			while (std::getline(sep, field, ','))
			{
				fields.back().push_back(std::stod(field));
			}
		}
	}
	else
		std::cerr << "Unable to open file path: " << filePath << "!" << std::endl;
}

void TileManager::LoadTiles(const std::vector<std::vector<int>>& tiles)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		mTiles.push_back({});

		for (int j = 0; j < tiles[i].size(); j++)
		{
			std::string texture;

			switch (tiles[i][j])
			{
			case 0:
				texture = "Tiles/tileGrass_roadCornerLL.png";
				break;
			case 1:
				texture = "Tiles/tileGrass_roadCornerLR.png";
				break;
			case 2:
				texture = "Tiles/tileGrass_roadCornerUL.png";
				break;
			case 3:
				texture = "Tiles/tileGrass_roadCornerUR.png";
				break;
			case 4:
				texture = "Tiles/tileGrass_roadCrossing.png";
				break;
			case 5:
				texture = "Tiles/tileGrass_roadCrossingRound.png";
				break;
			case 6:
				texture = "Tiles/tileGrass_roadEast.png";
				break;
			case 7:
				texture = "Tiles/tileGrass_roadNorth.png";
				break;
			case 8:
				texture = "Tiles/tileGrass_roadSplitE.png";
				break;
			case 9:
				texture = "Tiles/tileGrass_roadSplitN.png";
				break;
			case 10:
				texture = "Tiles/tileGrass_roadSplitS.png";
				break;
			case 11:
				texture = "Tiles/tileGrass_roadSplitW.png";
				break;
			case 12:
				texture = "Tiles/tileGrass_roadTransitionE.png";
				break;
			case 13:
				texture = "Tiles/tileGrass_roadTransitionE_dirt.png";
				break;
			case 14:
				texture = "Tiles/tileGrass_roadTransitionN.png";
				break;
			case 15:
				texture = "Tiles/tileGrass_roadTransitionN_dirt.png";
				break;
			case 16:
				texture = "Tiles/tileGrass_roadTransitionS.png";
				break;
			case 17:
				texture = "Tiles/tileGrass_roadTransitionS_dirt.png";
				break;
			case 18:
				texture = "Tiles/tileGrass_roadTransitionW.png";
				break;
			case 19:
				texture = "Tiles/tileGrass_roadTransitionW_dirt.png";
				break;
			case 20:
				texture = "Tiles/tileGrass_transitionE.png";
				break;
			case 21:
				texture = "Tiles/tileGrass_transitionN.png";
				break;
			case 22:
				texture = "Tiles/tileGrass_transitionS.png";
				break;
			case 23:
				texture = "Tiles/tileGrass_transitionW.png";
				break;
			case 24:
				if (rand() % 2)
					texture = "Tiles/tileGrass1.png";
				else
					texture = "Tiles/tileGrass2.png";
				break;
			case 25:
				texture = "Tiles/tileSand_roadCornerLL.png";
				break;
			case 26:
				texture = "Tiles/tileSand_roadCornerLR.png";
				break;
			case 27:
				texture = "Tiles/tileSand_roadCornerUL.png";
				break;
			case 28:
				texture = "Tiles/tileSand_roadCornerUR.png";
				break;
			case 29:
				texture = "Tiles/tileSand_roadCrossing.png";
				break;
			case 30:
				texture = "Tiles/tileSand_roadCrossingRound.png";
				break;
			case 31:
				texture = "Tiles/tileSand_roadEast.png";
				break;
			case 32:
				texture = "Tiles/tileSand_roadNorth.png";
				break;
			case 33:
				texture = "Tiles/tileSand_roadSplitE.png";
				break;
			case 34:
				texture = "Tiles/tileSand_roadSplitN.png";
				break;
			case 35:
				texture = "Tiles/tileSand_roadSplitS.png";
				break;
			case 36:
				texture = "Tiles/tileSand_roadSplitW.png";
				break;
			case 37:
				if (rand() % 2)
					texture = "Tiles/tileSand1.png";
				else
					texture = "Tiles/tileSand2.png";
				break;
			default:
				texture = "Tiles/tileGrass1.png";
			}

			mTiles.back().push_back(new Texture(texture));
			mTiles.back().back()->Parent(this);
			mTiles.back().back()->Pos(Vector2(j * 64 + 32, i * 64 + 32));

			if ((j < 1 || j > 14) || (i < 1 || i > 12))
			{
				switch (tiles[i][j])
				{
				case 6:
				case 7:
				case 31:
				case 32:
					if (i < 1)
						mSpawnPos.push_back(Vector2(mTiles.back().back()->Pos().x, -50.0f));
					else if (i > 12)
						mSpawnPos.push_back(Vector2(mTiles.back().back()->Pos().x, Graphics::SCREEN_HEIGHT + 50.0f));
					else if (j < 1)
						mSpawnPos.push_back(Vector2(-50.0f, mTiles.back().back()->Pos().y));
					else if (j > 14)
						mSpawnPos.push_back(Vector2(Graphics::SCREEN_WIDTH + 50.0f, mTiles.back().back()->Pos().y));
					break;
				}
			}
		}
	}
}

void TileManager::LoadObjects(const std::vector<std::vector<float>>& objects)
{
	for (int i = 0; i < objects.size(); i++)
	{
		std::string texture;
		bool passable;
		bool shootable;

		switch (static_cast<int>(objects[i][0]))
		{
		case -1:
			break;
		case 0:
			texture = "Objects/barrelBlack_side.png";
			passable = false;
			shootable = false;
			break;
		case 1:
			texture = "Objects/barrelBlack_top.png";
			passable = false;
			shootable = false;
			break;
		case 2:
			texture = "Objects/barrelGreen_side.png";
			passable = false;
			shootable = false;
			break;
		case 3:
			texture = "Objects/barrelGreen_top.png";
			passable = false;
			shootable = false;
			break;
		case 4:
			texture = "Objects/barrelRed_side.png";
			passable = false;
			shootable = false;
			break;
		case 5:
			texture = "Objects/barrelRed_top.png";
			passable = false;
			shootable = false;
			break;
		case 6:
			texture = "Objects/barrelRust_side.png";
			passable = false;
			shootable = false;
			break;
		case 7:
			texture = "Objects/barrelRust_top.png";
			passable = false;
			shootable = false;
			break;
		case 8:
			texture = "Objects/barricadeMetal.png";
			passable = false;
			shootable = true;
			break;
		case 9:
			texture = "Objects/barricadeWood.png";
			passable = false;
			shootable = true;
			break;
		case 10:
			texture = "Objects/crateMetal.png";
			passable = false;
			shootable = false;
			break;
		case 11:
			texture = "Objects/crateMetal_side.png";
			passable = false;
			shootable = false;
			break;
		case 12:
			texture = "Objects/crateWood.png";
			passable = false;
			shootable = false;
			break;
		case 13:
			texture = "Objects/crateWood_side.png";
			passable = false;
			shootable = false;
			break;
		case 14:
			texture = "Objects/fenceRed.png";
			passable = false;
			shootable = true;
			break;
		case 15:
			texture = "Objects/fenceYellow.png";
			passable = false;
			shootable = true;
			break;
		case 16:
			texture = "Objects/oilSpill_large.png";
			passable = true;
			shootable = true;
			break;
		case 17:
			texture = "Objects/oilSpill_small.png";
			passable = true;
			shootable = true;
			break;
		case 18:
			texture = "Objects/sandbagBeige.png";
			passable = false;
			shootable = true;
			break;
		case 19:
			texture = "Objects/sandbagBeige_open.png";
			passable = false;
			shootable = true;
			break;
		case 20:
			texture = "Objects/sandbagBrown.png";
			passable = false;
			shootable = true;
			break;
		case 21:
			texture = "Objects/sandbagBrown_open.png";
			passable = false;
			shootable = true;
			break;
		case 22:
			texture = "Objects/treeBrown_large.png";
			passable = false;
			shootable = false;
			break;
		case 23:
			texture = "Objects/treeBrown_leaf.png";
			passable = true;
			shootable = true;
			break;
		case 24:
			texture = "Objects/treeBrown_small.png";
			passable = false;
			shootable = false;
			break;
		case 25:
			texture = "Objects/treeBrown_twigs.png";
			passable = true;
			shootable = true;
			break;
		case 26:
			texture = "Objects/treeGreen_large.png";
			passable = false;
			shootable = false;
			break;
		case 27:
			texture = "Objects/treeGreen_leaf.png";
			passable = true;
			shootable = true;
			break;
		case 28:
			texture = "Objects/treeGreen_small.png";
			passable = false;
			shootable = false;
			break;
		case 29:
			texture = "Objects/treeGreen_twigs.png";
			passable = true;
			shootable = true;
			break;
		case 30:
			texture = "Objects/wireCrooked.png";
			passable = true;
			shootable = true;
			break;
		case 31:
			texture = "Objects/wireStraight.png";
			passable = true;
			shootable = true;
			break;
		default:
			std::cerr << "Tried loding an invalid object!" << std::endl;
			return;
		}

		if (objects[i][0] != -1)
		{
			Texture *tex = new Texture(texture);
			mObjects.push_back(new Tile(tex, Vector2(objects[i][1], objects[i][2]), passable, shootable));
			mObjects.back()->Rotation(objects[i][3]);
		}
	}
}

void TileManager::LoadMap(const std::vector<std::vector<int>>& tiles, const std::vector<std::vector<float>>& objects)
{
	LoadTiles(tiles);
	std::random_shuffle(mSpawnPos.begin(), mSpawnPos.end());
	LoadObjects(objects);
}

void TileManager::Update()
{
	for (auto &object : mObjects)
		object->Update();
}

void TileManager::Render()
{
	for (int i = 0; i < mTiles.size(); i++)
	{
		for (int j = 0; j < mTiles[i].size(); j++)
		{
			mTiles[i][j]->Render();
		}
	}

	for (const auto &object : mObjects)
		object->Render();
}