#ifndef RAIDER_H
#define RAIDER_H

#include "Enemy.h"

class Raider : public Enemy
{
private:
	void HandleSpawning();
	void HandleLiving();
	void HandleDeath();

	void HandleMovement();
	void HandleFiring();

public:
	Raider(Vector2 pos);
	~Raider();
};

#endif