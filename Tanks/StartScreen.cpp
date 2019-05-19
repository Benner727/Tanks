#include "StartScreen.h"

StartScreen::StartScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mLogo = new Texture("Tanks", "Fonts/Kenney Pixel Square.ttf", 178, { 94, 124, 22 });
	mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.33f, Graphics::Instance()->SCREEN_HEIGHT * 0.33f));
	mLogo->Parent(this);
	mLogo->Rotate(-45.0f);

	mMenuOptions = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.7f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mStartGame = new Texture("Play Game", "Fonts/Kenney Pixel Square.ttf", 32, { 45, 45, 45 });
	mInstructions = new Texture("Instructions", "Fonts/Kenney Pixel Square.ttf", 32, { 45, 45, 45 });
	
	mStartGame->Parent(mMenuOptions);
	mInstructions->Parent(mMenuOptions);
	mMenuOptions->Parent(this);

	mStartGame->Pos(Vector2(0.0f, -35.0f));
	mInstructions->Pos(Vector2(0.0f, 35.0f));

	mBottomBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.95f));
	mCreator = new Texture("Created by Stephen Benner", "Fonts/Kenney Pixel.ttf", 32, { 47, 79, 79 });
	mAssets = new Texture("Assets by Kenney Vleugels", "Fonts/Kenney Pixel.ttf", 32, { 47, 79, 79 });
	mPatch = new Texture("Patch 1.0", "Fonts/Kenney Pixel.ttf", 16, { 32, 32, 32 });

	mCreator->Parent(mBottomBar);
	mAssets->Parent(mBottomBar);
	mPatch->Parent(mBottomBar);
	mBottomBar->Parent(this);

	mCreator->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.15f, 30.0f));
	mAssets->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.15f, 30.0f));
	mPatch->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.46f, -Graphics::Instance()->SCREEN_HEIGHT * 0.93f));

	mSelectedOption = 0;
	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.33f;
	mSelectedOptionVisible = true;
}


StartScreen::~StartScreen()
{
	mTimer = nullptr;
	mInput = nullptr;

	delete mLogo;
	mLogo = nullptr;

	delete mCreator;
	mCreator = nullptr;

	delete mAssets;
	mAssets = nullptr;

	delete mPatch;
	mPatch = nullptr;

	delete mBottomBar;
	mBottomBar = nullptr;
}

int StartScreen::SelectedOption()
{
	return mSelectedOption;
}

void StartScreen::ChangeSelectedOption(int change)
{
	mSelectedOption += change;

	if (mSelectedOption < 0)
		mSelectedOption = 1;
	else if (mSelectedOption > 1)
		mSelectedOption = 0;
}

void StartScreen::Update()
{
	if (mInput->KeyPressed(SDL_SCANCODE_DOWN))
		ChangeSelectedOption(1);
	else if (mInput->KeyPressed(SDL_SCANCODE_UP))
		ChangeSelectedOption(-1);

	mBlinkTimer += mTimer->DeltaTime();
	if (mBlinkTimer >= mBlinkInterval)
	{
		mSelectedOptionVisible = !mSelectedOptionVisible;
		mBlinkTimer = 0.0f;
	}

	if (mInput->KeyPressed(SDL_SCANCODE_DOWN) || mInput->KeyPressed(SDL_SCANCODE_UP))
	{
		mBlinkTimer = 0.0f;
		mSelectedOptionVisible = true;
	}
}

void StartScreen::Render()
{

	mLogo->Render();

	if ((mSelectedOption == 0 && mSelectedOptionVisible) || mSelectedOption != 0)
		mStartGame->Render();
	if ((mSelectedOption == 1 && mSelectedOptionVisible) || mSelectedOption != 1)
		mInstructions->Render();

	mCreator->Render();
	mAssets->Render();
	mPatch->Render();
}