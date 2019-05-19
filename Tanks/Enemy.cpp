#include "Enemy.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
#include "Tile.h"

Enemy::Enemy()
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mCurrentState = spawning;

	mTank = nullptr;

	mBarrel = nullptr;

	mValue = 0;

	mDeathAnimation = new AnimatedTexture("Player/explosion.png", 0, 0, 64, 63, 5, 1.25f, AnimatedTexture::horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Pos(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::once);

	mTarget = nullptr;

	mPosTimer = 0.0f;
	mPosDelay = 3.0f;
	mAngle = Rotation();

	mAcceleration = 40.0f;
	mRotationSpeed = 15.0f;

	mSpawnTimer = 0.0f;
	mSpawned = false;
	mAnimating = false;
	mDead = false;

	mHitCounter = 0;
	mFlying = false;

	mReloadTimer = 0.0f;
	mFireRate = 3.0f;

	mCollisionLayer = PhysEntity::CollisionLayers::Hostile;
	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);
}

Enemy::~Enemy()
{
	mTimer = nullptr;
	mAudio = nullptr;

	delete mTank;
	mTank = nullptr;

	delete mBarrel;
	mBarrel = nullptr;

	delete mDeathAnimation;
	mDeathAnimation = nullptr;

	for (int i = 0; i < mBullets.size(); i++)
	{
		delete mBullets[i];
		mBullets[i] = nullptr;
	}

	mBullets.clear();

	for (int i = 0; i < mParticles.size(); i++)
	{
		delete mParticles[i];
		mParticles[i] = nullptr;
	}

	mParticles.clear();

	mTarget = nullptr;
}

void Enemy::HandleTracks()
{

}

void Enemy::HandleSpawning()
{

}

void Enemy::HandleLiving()
{

}

void Enemy::HandleDeath()
{

}

void Enemy::HandleStates()
{
	switch (mCurrentState)
	{
	case spawning:
		HandleSpawning();
		break;
	case alive:
		HandleLiving();
		break;
	case dead:
		HandleDeath();
		break;
	}
}

void Enemy::Target(GameEntity* target)
{
	mTarget = target;
}

bool Enemy::IgnoreCollisions()
{
	return mAnimating;
}

bool Enemy::IsAnimating()
{
	return mAnimating;
}

void Enemy::Hit(PhysEntity* other)
{
	if (mSpawned && !mDead)
	{
		if (other->CollisionLayer() == CollisionLayers::FriendlyProjectiles)
		{
			mHitCounter++;
			mTank->Flash();
		}
		else
		{
			if (other->CollisionLayer() == CollisionLayers::Object)
			{
				if (static_cast<Tile*> (other)->Passable() || mFlying)
					return;
			}

			if (mColliders[0]->GetMTV().mValid)
			{
				if (Dot(Pos() - other->Pos(), mColliders[0]->GetMTV().mAxis) < 0.0f)
				{
					if (other->CollisionLayer() != CollisionLayers::Hostile || mFlying)
					{
						if(!mFlying)
							Translate(-mColliders[0]->GetMTV().mOverlap * mColliders[0]->GetMTV().mAxis);
					}
					else
						Translate(VEC2_UP * mAcceleration * mTimer->DeltaTime(), local);
				}
				else
				{
					if (other->CollisionLayer() != CollisionLayers::Hostile)
					{
						if (!mFlying)
							Translate(mColliders[0]->GetMTV().mOverlap * mColliders[0]->GetMTV().mAxis);
					}
				}
			}
		}
	}
}

bool Enemy::Dead()
{
	return mDead;
}

void Enemy::Update()
{
	HandleTracks();

	if (Active())
	{
		if (mAnimating)
		{
			mDeathAnimation->Update();
			mAnimating = mDeathAnimation->IsAnimating();
			mDead = !mAnimating;
		}
		else
			HandleStates();
	}

	if (mPosTimer > 0)
	{
		mPosTimer -= mTimer->DeltaTime();

		if (mPosTimer < 0)
			mPosTimer = 0;
	}

	if (mReloadTimer > 0)
	{
		mReloadTimer -= mTimer->DeltaTime();

		if (mReloadTimer < 0)
			mReloadTimer = 0;
	}

	for (auto &bullet : mBullets)
		bullet->Update();
}

void Enemy::Render()
{
	for (const auto &particle : mParticles)
		particle->Render();

	if (Active())
	{
		if (mAnimating)
			mDeathAnimation->Render();
		else if (!mDead)
		{
			mTank->Render();
			mBarrel->Render();
		}
	}

	for (const auto &bullet : mBullets)
		bullet->Render();

	PhysEntity::Render();
}