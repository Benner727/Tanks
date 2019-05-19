#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "Texture.h"
#include <vector>

class Scoreboard : public GameEntity
{
public:
	Scoreboard(SDL_Color color = { 255, 255, 255 });
	~Scoreboard();

private:
	std::vector<Texture*> mScore;

	SDL_Color mColor;

	void ClearBoard();

public:
	void Color(SDL_Color color);
	void Score(int score);

	void Render();
};

#endif