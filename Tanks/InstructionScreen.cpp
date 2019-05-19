#include "InstructionScreen.h"

InstructionScreen::InstructionScreen()
{
	mTimer = Timer::Instance();

	mInstructions = new Texture("INSTRUCTIONS", "Fonts/Kenney Pixel Square.ttf", 74, { 94, 124, 22 });
	mInstructions->Parent(this);
	mInstructions->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5, Graphics::SCREEN_HEIGHT * 0.1f));

	mControlInfo = new GameEntity();
	mControlInfo->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5, Graphics::SCREEN_HEIGHT * 0.25f));
	mControlInfo->Parent(this);

	mControls = new Texture("CONTROLS", "Fonts/Kenney Pixel Square.ttf", 56, { 240, 200, 0 });
	mMovement = new Texture("Use 'WASD' to move.", "Fonts/Kenney Pixel Square.ttf", 32, { 45, 45, 45 });
	mAim = new Texture("Use your mouse to aim.", "Fonts/Kenney Pixel Square.ttf", 32, { 45, 45, 45 });
	mFiring = new Texture("Press 'SPACEBAR' to shoot.", "Fonts/Kenney Pixel Square.ttf", 32, { 45, 45, 45 });

	mControls->Parent(mControlInfo);
	mMovement->Parent(mControlInfo);
	mAim->Parent(mControlInfo);
	mFiring->Parent(mControlInfo);

	mControls->Pos(Vector2(VEC2_ZERO));
	mMovement->Pos(Vector2(0.0f, 60.0f));
	mAim->Pos(Vector2(0.0f, 110.0f));
	mFiring->Pos(Vector2(0.0f, 160.0f));

	mEscape = new Texture("Press 'ESCAPE' to return to start screen.", "Fonts/Kenney Pixel Square.ttf", 32, { 47, 79, 79 });
	mEscape->Parent(this);
	mEscape->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5, Graphics::SCREEN_HEIGHT * 0.95f));

	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.5f;
	mEscapeVisible = true;
}

InstructionScreen::~InstructionScreen()
{
	mTimer = nullptr;

	delete mInstructions;
	mInstructions = nullptr;

	delete mControls;
	mControls = nullptr;

	delete mMovement;
	mMovement = nullptr;

	delete mAim;
	mAim = nullptr;

	delete mFiring;
	mFiring = nullptr;

	delete mControlInfo;
	mControlInfo = nullptr;

	delete mEscape;
	mEscape = nullptr;
}

void InstructionScreen::Update()
{
	mBlinkTimer += mTimer->DeltaTime();
	if (mBlinkTimer >= mBlinkInterval)
	{
		mEscapeVisible = !mEscapeVisible;
		mBlinkTimer = 0.0f;
	}
}

void InstructionScreen::Render()
{
	mInstructions->Render();

	mControls->Render();
	mMovement->Render();
	mAim->Render();
	mFiring->Render();

	if (mEscapeVisible)
		mEscape->Render();
}