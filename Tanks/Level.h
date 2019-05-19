#ifndef LEVEL_H
#define LEVEL_H

#include "PlayerUI.h"
#include "Player.h"
#include "TileManager.h"
#include "Enemy.h"

class Level : public GameEntity
{
public:
	enum LEVEL_STATES { running, levelover, gameover };

private:
	Timer* mTimer;

	TileManager* mTileManager;

	PlayerUI* mPlayerUI;
	Player* mPlayer;

	std::vector<Enemy*> mEnemy;

	int mLevel;
	int mNumberOfEnemies;
	bool mLevelStarted;

	Texture* mGameOverLabel;
	bool mGameOver;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverLabelOnScreen;

	LEVEL_STATES mCurrentState;

	float mSpawnDelay;
	float mSpawnTimer;
	int mSpawn;

	void KillEnemies();
	void HandleEnemies();

public:
	Level(PlayerUI* playerUI, Player* player);
	~Level();

	LEVEL_STATES State();

	void SetCurrentLevel(int level);
	void StartLevel();

	void Update();
	void Render();
};

#endif