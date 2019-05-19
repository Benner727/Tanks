#include "Scout.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Scout::Scout(Vector2 pos)
{
	Pos(pos);

	mTank = new Texture("Player/tankBody_dark_outline.png");
	mTank->Parent(this);
	mTank->Pos(VEC2_ZERO);

	mBarrel = new Texture("Player/tankDark_barrel2_outline.png");
	mBarrel->Parent(this);
	mBarrel->Pos(Vector2(0.0f, 2.0f));

	mValue = 100;

	mAcceleration = 40.0f;
	mRotationSpeed = 20.0f;

	mSpawnTimer = rand() % 3 + 1;
	
	mFireRate += rand() % 2;

	for (int i = 0; i < 3; i++)
		mBullets.push_back(new Bullet(false, 0));

	AddCollider(new BoxCollider(mTank->ScaledDimensions()));

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

Scout::~Scout()
{
}

void Scout::HandleTracks()
{
	for (int i = 0; i < mParticles.size(); i++)
	{
		mParticles[i]->Update();

		if (mParticles[i]->Dead())
		{
			delete mParticles[i];
			mParticles[i] = nullptr;

			mParticles.erase(mParticles.begin() + i);
		}
	}
}

void Scout::HandleMovement()
{
	if ((Pos(GameEntity::world) - mTarget->Pos()).Magnitude() > 250.0f)
	{
		if (!mPosTimer)
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
		}

		float difference = Rotation() - mAngle;
		if (difference < 0.0f) difference += 360.0f;

		if (difference < 180.0f)
			Rotate(-mRotationSpeed * mTimer->DeltaTime());
		else if (difference > 180.0f)
			Rotate(mRotationSpeed * mTimer->DeltaTime());

		//Move tank
		Translate(-VEC2_UP * mAcceleration * mTimer->DeltaTime(), local);

		//Spawn tracks
		if (!(rand() % 12))
			mParticles.push_back(new Particle(Pos(), Rotation()));
	}

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
}

void Scout::HandleFiring()
{
	if (mTarget->Active())
	{
		Vector2 direction = (Pos(GameEntity::world) - mTarget->Pos()).Normalize();
		float angle = atan2(direction.y, direction.x) * RAD_TO_DEG;
		mBarrel->Rotation(angle + 90.0f - Rotation());

		if (mReloadTimer > 0 || mSpawnTimer > 0.0f)
			return;
		else if ((Pos(GameEntity::world) - mTarget->Pos()).Magnitude() < 600.0f)
		{
			mBarrel->Rotate(rand() % 2 ? -rand() % 5 : rand() % 5);

			for (int i = 0; i < mBullets.size(); i++)
			{
				if (!mBullets[i]->Animating())
				{
					mAudio->PlaySFX("explodemini.wav");
					mBullets[i]->Fire(mBarrel->Pos(), mBarrel->Rotation() - 180);
					mReloadTimer = mFireRate;
					break;
				}
			}
		}
	}
}

void Scout::HandleSpawning()
{
	if ((Pos().x > mTank->ScaledDimensions().x * 0.5f && Pos().x < Graphics::SCREEN_WIDTH - mTank->ScaledDimensions().x * 0.5f)
		&& (Pos().y > mTank->ScaledDimensions().y * 0.5f && Pos().y < Graphics::SCREEN_HEIGHT - mTank->ScaledDimensions().y * 0.5f))
	{
		mSpawned = true;
		mCurrentState = alive;
	}
	else
	{
		//Move tank
		Translate(-VEC2_UP * mAcceleration * mTimer->DeltaTime(), local);
	}
}

void Scout::HandleLiving()
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

void Scout::HandleDeath()
{
	mDead = true;
}