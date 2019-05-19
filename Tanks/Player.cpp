#include "Player.h"

Player::Player()
{
	mInput = InputManager::Instance();

	mTank = new Tank;
	mTank->Parent(this);
	mTank->Pos(VEC2_ZERO);

	mScore = 0;

	Reset();
}

Player::~Player()
{
	mInput = nullptr;

	delete mTank;
	mTank = nullptr;
}

void Player::Reset()
{
	mTank->Reset();
}

void Player::HandleMovement()
{
	//Apply forward acceleration
	if (mInput->KeyDown(SDL_SCANCODE_W))
	{
		mTank->Accelerate(true);
	}

	//Apply backward acceleration
	if (mInput->KeyDown(SDL_SCANCODE_S))
	{
		mTank->Accelerate(false);
	}

	//Subtract from rotation
	if (mInput->KeyDown(SDL_SCANCODE_A))
	{
		mTank->Turn(false);
	}

	//Add to rotation
	if (mInput->KeyDown(SDL_SCANCODE_D))
	{
		mTank->Turn(true);
	}
}

void Player::HandleFiring()
{
	mTank->Aim(mInput->MousePos());

	if (mInput->KeyDown(SDL_SCANCODE_SPACE))
	{
		mTank->Fire();
	}
}

void Player::Visible(bool visible)
{
	mTank->Visible(visible);
}

int Player::Health()
{
	return mTank->Health();
}

bool Player::Dead()
{
	return mTank->Dead();
}

bool Player::IsAnimating()
{
	return mTank->IsAnimating();
}

Tank* Player::GetTank()
{
	return mTank;
}

void Player::Update()
{
	mTank->Update();

	if (Active())
	{
		HandleMovement();
		HandleFiring();
	}
}

void Player::Render()
{
	mTank->Render();
}