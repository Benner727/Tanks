#ifndef PLAYERUI_H
#define PLAYERUI_H

#include "ScoreBoard.h"

class PlayerUI : public GameEntity
{
private:
	Scoreboard* mScore;
	Scoreboard* mLevel;
	Texture* mHealthBar;

public:
	PlayerUI();
	~PlayerUI();

	void Score(int score);
	void Level(int level);
	void Health(int health);

	void Update();
	void Render();
};

#endif