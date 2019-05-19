#include "Scoreboard.h"

Scoreboard::Scoreboard(SDL_Color color)
{
	mColor = color;
	Score(0);
}

Scoreboard::~Scoreboard()
{
	ClearBoard();
}

void Scoreboard::ClearBoard()
{
	for (int i = 0; i < mScore.size(); i++)
	{
		delete mScore[i];
		mScore[i] = nullptr;
	}

	mScore.clear();
}

void Scoreboard::Color(SDL_Color color)
{
	mColor = color;
}

void Scoreboard::Score(int score)
{
	ClearBoard();

	std::string str = std::to_string(score);

	int lastIndex = str.length() - 1;

	for (int i = 0; i <= lastIndex; i++)
	{
		mScore.push_back(new Texture(str.substr(i,1), "Fonts/Kenney Pixel Square.ttf", 20, mColor));
		mScore[i]->Parent(this);

		if (i < lastIndex / 2)
			mScore[i]->Pos(Vector2(-17.0f * (lastIndex / 2 - i), 0.0f));
		else
			mScore[i]->Pos(Vector2(17.0f * (i - lastIndex / 2), 0.0f));
	}
}

void Scoreboard::Render()
{
	for (const auto &score : mScore)
		score->Render();
}