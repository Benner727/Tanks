#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mCurrentLevel = 1;
	mLevelLabel = nullptr;

	mLevelStartDelay = 4.0f;
	mLevelStartTimer = mLevelStartDelay;
	mLevelStarted = false;

	mLevel = nullptr;

	mPlayerUI = nullptr;
	mPlayer = nullptr;
}


PlayScreen::~PlayScreen()
{
	mTimer = nullptr;
	mInput = nullptr;

	delete mLevel;
	mLevel = nullptr;

	delete mPlayerUI;
	mPlayerUI = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	delete mLevelLabel;
	mLevelLabel = nullptr;
}

void PlayScreen::StartNewGame()
{
	delete mPlayer;
	mPlayer = new Player();

	mPlayerUI = new PlayerUI();
	mPlayerUI->Parent(this);
	mPlayerUI->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, 30.0f));

	mCurrentLevel = 1;
	mLevelLabel = new Texture("Level " + std::to_string(mCurrentLevel), "Fonts/Kenney Pixel Square.ttf", 36, { 204, 0, 0 });
	mLevelLabel->Parent(this);
	mLevelLabel->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.15f));

	mLevelStartTimer = mLevelStartDelay;
	mLevelStarted = false;

	delete mLevel;
	mLevel = new Level(mPlayerUI, mPlayer);
	mLevel->SetCurrentLevel(mCurrentLevel);
}

void PlayScreen::StartNextLevel()
{
	mCurrentLevel++;
	mLevelStartTimer = mLevelStartDelay;
	mLevelStarted = false;

	delete mLevelLabel;
	mLevelLabel = new Texture("Level " + std::to_string(mCurrentLevel), "Fonts/Kenney Pixel Square.ttf", 36, { 204, 0, 0 });
	mLevelLabel->Parent(this);
	mLevelLabel->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.15f));

	mLevel->SetCurrentLevel(mCurrentLevel);
}

bool PlayScreen::GameOver()
{
	return (mLevel->State() == Level::gameover);
}

void PlayScreen::Update()
{
	mPlayerUI->Update();
	mPlayer->Update();

	if (!mLevelStarted)
	{
		if (mLevelStartTimer > 0.0f)
			mLevelStartTimer -= mTimer->DeltaTime();
		else
		{
			mLevelStarted = true;
			mLevel->StartLevel();
		}
	}
	else
	{
		mLevel->Update();
	}
}

void PlayScreen::Render()
{
	mLevel->Render();
	mPlayerUI->Render();
	//mPlayer->Render();

	if (!mLevelStarted)
	{
		if (mLevelStartTimer < mLevelStartDelay - 1.0f)
			mLevelLabel->Render();
	}
	else if (mLevel->State() == Level::levelover)
		StartNextLevel();
}