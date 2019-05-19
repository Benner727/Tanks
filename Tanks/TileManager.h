#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include "Tile.h"
#include <vector>

class TileManager : public GameEntity
{
private:
	static TileManager* sInstance;

	std::vector<std::vector<Texture*>> mTiles;
	std::vector<Tile*> mObjects;
	std::vector<Vector2> mSpawnPos;

	TileManager();
	~TileManager();

	void ReadMap(std::string filePath, std::vector<std::vector<int>> &fields);
	void ReadObjects(std::string filePath, std::vector<std::vector<float>> &fields);

	void LoadTiles(const std::vector<std::vector<int>>&);
	void LoadObjects(const std::vector<std::vector<float>>&);
public:
	static TileManager* Instance();
	static void Release();

	void LoadMap(const std::vector<std::vector<int>>&, const std::vector<std::vector<float>>&);
	std::vector<Vector2> SpawnPos() const { return mSpawnPos; }

	void Update();
	void Render();
};

#endif