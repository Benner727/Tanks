#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = nullptr;

ScreenManager* ScreenManager::Instance()
{
	if (sInstance == nullptr)
		sInstance = new ScreenManager();

	return sInstance;
}

void ScreenManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

ScreenManager::ScreenManager()
{
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mAudio->PlayMusic("Gregoire_Lourme_-_Commando_Team_Action.wav");
	
	mBackground = new Background();

	mPauseLabel= new Texture("P A U S E D", "Fonts/Kenney Pixel Square.ttf", 74, { 0, 0, 0 });
	mPauseLabel->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));

	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();
	mInstructionScreen = new InstructionScreen();

	mCurrentScreen = start;
}

ScreenManager::~ScreenManager()
{
	mInput = nullptr;
	mAudio = nullptr;

	delete mBackground;
	mBackground = nullptr;

	delete mPauseLabel;
	mPauseLabel = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;

	delete mInstructionScreen;
	mInstructionScreen = nullptr;
}

void ScreenManager::Update()
{
	if (mCurrentScreen != play && mCurrentScreen != pause)
		mBackground->Update();

	switch (mCurrentScreen)
	{
	case start:
		mStartScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN))
		{
			if (mStartScreen->SelectedOption() == 0)
			{
				mCurrentScreen = play;
				mPlayScreen->StartNewGame();
				mAudio->PauseMusic();
			}
			else if (mStartScreen->SelectedOption() == 1)
			{
				mCurrentScreen = instruction;
			}
		}
		break;
	case play:
		mPlayScreen->Update();

		if (mPlayScreen->GameOver())
		{
			mCurrentScreen = start;
			mBackground->Restart();
			mAudio->ResumeMusic();
		}
		else if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE))
			mCurrentScreen = pause;
		break;
	case pause:
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE))
			mCurrentScreen = play;
		break;
	case instruction:
		mInstructionScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE))
			mCurrentScreen = start;
		break;
	}
}

void ScreenManager::Render()
{
	if (mCurrentScreen != play && mCurrentScreen != pause)
		mBackground->Render();

	switch (mCurrentScreen)
	{
	case start:
		mStartScreen->Render();
		break;
	case play:
		mPlayScreen->Render();
		break;
	case pause:
		mPlayScreen->Render();
		mPauseLabel->Render();
		break;
	case instruction:
		mInstructionScreen->Render();
		break;
	}
}