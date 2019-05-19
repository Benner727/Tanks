#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "Background.h"
#include "Timer.h"
#include "InputManager.h"

class StartScreen : public GameEntity
{
public:
	StartScreen();
	~StartScreen();

private:
	Timer* mTimer;
	InputManager* mInput;

	Texture* mLogo;

	GameEntity* mMenuOptions;
	Texture* mStartGame;
	Texture* mInstructions;

	GameEntity* mBottomBar;
	Texture* mCreator;
	Texture* mAssets;
	Texture* mPatch;

	int mSelectedOption;
	float mBlinkTimer;
	float mBlinkInterval;
	bool mSelectedOptionVisible;

public:
	int SelectedOption();

	void ChangeSelectedOption(int change);

	void Update();
	void Render();
};

#endif