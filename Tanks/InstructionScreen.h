#ifndef INSTRUCTIONSCREEN_H
#define INSTRUCTIONSCREEN_H

#include "Texture.h"
#include "Timer.h"

class InstructionScreen : public GameEntity
{
public:
	InstructionScreen();
	~InstructionScreen();

private:
	Timer* mTimer;

	Texture* mInstructions;

	GameEntity* mControlInfo;
	Texture* mControls;
	Texture* mMovement;
	Texture* mAim;
	Texture* mFiring;

	Texture* mEscape;
	float mBlinkTimer;
	float mBlinkInterval;
	bool mEscapeVisible;

public:
	void Update();
	void Render();
};

#endif