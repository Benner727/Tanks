#ifndef PLAYER_H
#define PLAYER_H

#include "InputManager.h"
#include "Tank.h"

class Player : public GameEntity
{
private:
	InputManager* mInput;

	Tank* mTank;

	int mScore;

	void HandleMovement();
	void HandleFiring();

public:
	Player();
	~Player();

	void Reset();

	void Visible(bool visible);

	void Heal() { mTank->Heal(); }
	int Health();
	bool Dead();

	bool IsAnimating();

	Tank* GetTank();

	void AddScore(int change) { mScore += change; }
	int Score() const { return mScore; }

	void Update();
	void Render();
};

#endif