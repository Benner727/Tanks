#include "Raider.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Raider::Raider(Vector2 pos)
{
	Pos(pos);

	mTank = new Texture("Player/plane.png");
	mTank->Parent(this);
	mTank->Pos(VEC2_ZERO);

	mBarrel = new Texture("Player/shadow.png");
	mBarrel->Parent(this);
	mBarrel->Pos(VEC2_ZERO);

	mTank->Rotate(90.0f);
	mBarrel->Rotate(90.0f);

	mValue = 100;

	mAcceleration = 75.0f;
	mRotationSpeed = 45.0f;

	mSpawnTimer = rand() % 3 + 1;

	mFireRate = 1.0f;

	mFlying = true;

	for (int i = 0; i < 3; i++)
		mBullets.push_back(new Bullet(false, 2));

	AddCollider(new BoxCollider(Vector2(20.0f, 60.0f), 90.0f), Vector2(0.0f, 5.0f));
	AddCollider(new BoxCollider(Vector2(20.0f, 50.0f)));
	

	if (Pos().x < mTank->ScaledDimensions().x * 0.5f)
		Rotation(270.0f);
	else if (Pos().x > Graphics::SCREEN_WIDTH - mTank->ScaledDimensions().x * 0.5f)
		Rotation(90.0f);
	else if (Pos().y < mTank->ScaledDimensions().y * 0.5f)
		Rotation(0.0f);
	else if (Pos().y > Graphics::SCREEN_HEIGHT - mTank->ScaledDimensions().y * 0.5f)
		Rotation(180.0f);

	mTarget = nullptr;
}


Raider::~Raider()
{
}

void Raider::HandleMovement()
{
	if (true)
	{
		Vector2 direction = (Pos(GameEntity::world) - mTarget->Pos()).Normalize();
		mAngle = atan2(direction.y, direction.x) * RAD_TO_DEG + (rand() % 90 + 45);

		while (mAngle > 360.0f || mAngle < 0.0f)
		{
			if (mAngle > 360.0f)
				mAngle -= 360.0f;
			else if (mAngle < 0.0f)
				mAngle += 360.0f;
		}

		mPosTimer = mPosDelay;

		float difference = Rotation() - mAngle;
		if (difference < 0.0f) difference += 360.0f;

		if (difference < 180.0f)
			Rotate(-mRotationSpeed * mTimer->DeltaTime());
		else if (difference > 180.0f)
			Rotate(mRotationSpeed * mTimer->DeltaTime());

		//Move tank
		Translate(-VEC2_UP * mAcceleration * mTimer->DeltaTime(), local);
	}

	/*
	//Keep tank on screen
	Vector2 pos = Pos(local);

	if (pos.x < mTank->ScaledDimensions().x * 0.5f)
		pos.x = mTank->ScaledDimensions().x * 0.5f;
	else if (pos.x > Graphics::SCREEN_WIDTH - mTank->ScaledDimensions().x * 0.5f)
		pos.x = Graphics::SCREEN_WIDTH - mTank->ScaledDimensions().x * 0.5f;

	if (pos.y < mTank->ScaledDimensions().y * 0.5f)
		pos.y = mTank->ScaledDimensions().y * 0.5f;
	else if (pos.y > Graphics::SCREEN_HEIGHT - mTank->ScaledDimensions().y * 0.5f)
		pos.y = Graphics::SCREEN_HEIGHT - mTank->ScaledDimensions().y * 0.5f;

	Pos(pos);
	*/
}

void Raider::HandleFiring()
{
	if (mTarget->Active())
	{
		float difference = Rotation() - mAngle;
		if (difference < 0.0f) difference += 360.0f;

		if (mReloadTimer > 0 || mSpawnTimer > 0.0f || (difference < 359.0f && difference > 1.0f))
			return;
		else if ((Pos(GameEntity::world) - mTarget->Pos()).Magnitude() < 400.0f)
		{
			for (int i = 0; i < mBullets.size(); i++)
			{
				if (!mBullets[i]->Animating())
				{
					mAudio->PlaySFX("explodemini.wav");
					mBullets[i]->Fire(Pos(), Rotation() - 180);
					mReloadTimer = mFireRate;
					break;
				}
			}
		}
	}
}

void Raider::HandleSpawning()
{
	if ((Pos().x > mTank->ScaledDimensions().x * 0.5f && Pos().x < Graphics::SCREEN_WIDTH - mTank->ScaledDimensions().x * 0.5f)
		&& (Pos().y > mTank->ScaledDimensions().y * 0.5f && Pos().y < Graphics::SCREEN_HEIGHT - mTank->ScaledDimensions().y * 0.5f))
	{
		mSpawned = true;
		mSpawnTimer = 0;
		mCurrentState = alive;
	}
	else
	{
		//Move tank
		Translate(-VEC2_UP * mAcceleration * mTimer->DeltaTime(), local);
	}
}

void Raider::HandleLiving()
{
	if (mHitCounter >= 1)
	{
		mCurrentState = dead;
		mAudio->PlaySFX("explode.wav");
		mDeathAnimation->ResetAnimation();
		mAnimating = true;
		return;
	}

	if (mSpawnTimer > 0.0f)
	{
		if ((Pos(GameEntity::world) - mTarget->Pos()).Magnitude() < 100.0f)
		{
			if (mSpawnTimer > 1.0f)
				mSpawnTimer = 1.0f;
		}

		mSpawnTimer -= mTimer->DeltaTime();
	}

	HandleMovement();
	HandleFiring();
}

void Raider::HandleDeath()
{

}