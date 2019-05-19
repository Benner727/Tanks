#ifndef SCOUT_H
#define SCOUT_H

#include "Enemy.h"

class Scout : public Enemy
{
private:
	void HandleSpawning();
	void HandleLiving();
	void HandleDeath();

	void HandleTracks();
	void HandleMovement();
	void HandleFiring();

public:
	Scout(Vector2 pos);
	~Scout();
};

#endif
