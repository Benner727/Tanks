#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Texture.h"
#include "Timer.h"
#include <vector>

enum DIRECTION {UP, DOWN, LEFT, RIGHT};

class Background : GameEntity
{
public:
	Background();
	~Background();

private:
	Timer* mTimer;

	std::vector<std::vector<Texture*>> mTiles;
	std::vector<Texture*> mObjects;
	Texture* mTank;

	void Initialize();

	void HandleTank();

public:
	void Restart();

	void Update();
	void Render();
};

#endif