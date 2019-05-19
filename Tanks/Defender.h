#ifndef DEFENDER_H
#define DEFENDER_H

#include "Enemy.h"

class Defender : public Enemy
{
private:
	void HandleSpawning();
	void HandleLiving();
	void HandleDeath();

	void HandleTracks();
	void HandleMovement();
	void HandleFiring();

public:
	Defender(Vector2 pos);
	~Defender();
};

#endif
