#include "PlayerUI.h"

PlayerUI::PlayerUI()
{
	mScore = new Scoreboard();
	mScore->Parent(this);
	mScore->Pos(Vector2(-Graphics::SCREEN_WIDTH * 0.45f, 0.0f));

	mLevel = new Scoreboard({ 255, 0, 0 });
	mLevel->Parent(this);
	mLevel->Pos(VEC2_ZERO);

	mHealthBar = new Texture("Player/healthbar.png", 228, 0, 57, 20);
	mHealthBar->Parent(this);
	mHealthBar->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.45f, 0.0f));
}


PlayerUI::~PlayerUI()
{
	delete mScore;
	mScore = nullptr;
}

void PlayerUI::Score(int score)
{
	mScore->Score(score);
}

void PlayerUI::Level(int level)
{
	mLevel->Score(level);
}

void PlayerUI::Health(int health)
{
	mHealthBar = new Texture("Player/healthbar.png", health  * 57, 0, 57, 20);
	mHealthBar->Parent(this);
	mHealthBar->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.45f, 0.0f));
}

void PlayerUI::Update()
{
	mScore->Update();
	mHealthBar->Update();
}

void PlayerUI::Render()
{
	mScore->Render();
	mLevel->Render();
	mHealthBar->Render();
}