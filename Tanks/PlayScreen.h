#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

#include "Level.h"
#include "PlayerUI.h"

class PlayScreen : public GameEntity
{
private:
	Timer *mTimer;
	InputManager* mInput;

	int mCurrentLevel;
	Texture* mLevelLabel;

	float mLevelStartDelay;
	float mLevelStartTimer;
	bool mLevelStarted;

	Level* mLevel;

	PlayerUI* mPlayerUI;
	Player* mPlayer;

public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame();
	void StartNextLevel();

	bool GameOver();

	void Update();
	void Render();
};

#endif