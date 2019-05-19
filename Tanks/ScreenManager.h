#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "Background.h"
#include "StartScreen.h"
#include "PlayScreen.h"
#include "InstructionScreen.h"

class ScreenManager
{
private:
	enum SCREENS { start, play, instruction, pause };

	static ScreenManager* sInstance;

	ScreenManager();
	~ScreenManager();

	InputManager* mInput;
	AudioManager* mAudio;

	Background* mBackground;
	Texture* mPauseLabel;

	StartScreen* mStartScreen;
	PlayScreen* mPlayScreen;
	InstructionScreen* mInstructionScreen;

	SCREENS mCurrentScreen;
public:
	static ScreenManager* Instance();

	static void Release();

	void Update();
	void Render();
};

#endif