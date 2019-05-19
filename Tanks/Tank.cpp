#include "Tank.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
#include "Tile.h"
#include "Enemy.h"

Tank::Tank()
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mVisible = true;
	mDead = false;
	mAnimating = false;

	mHealth = 4;

	mTank = new Texture("Player/tankBody_red_outline.png");
	mTank->Parent(this);
	mTank->Pos(VEC2_ZERO);

	mBarrel = new Texture("Player/tankRed_barrel2_outline.png");
	mBarrel->Parent(this);
	mBarrel->Pos(Vector2(0.0f, 2.0f));

	mDeathAnimation = new AnimatedTexture("Player/explosion.png", 0, 0, 64, 63, 5, 1.25f, AnimatedTexture::horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Pos(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::once);

	mReloadTimer = 0.0f;
	mFireRate = 1.0f;

	for (int i = 0; i < 3; i++)
		mBullets.push_back(new Bullet(true, 0));

	mAcceleration = 100.0f;
	mRotationSpeed = 1.5f;

	Reset();

	AddCollider(new BoxCollider(mTank->ScaledDimensions()));

	mCollisionLayer = CollisionLayers::Friendly;
	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);
}


Tank::~Tank()
{
	mTimer = nullptr;
	mAudio = nullptr;

	delete mTank;
	mTank = nullptr;

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
}

void Tank::Reset()
{
	Active(true);
	mDead = false;

	mOrientation = 0.0f;
	Rotation(180.0f);

	mVelocity = VEC2_ZERO;

	Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5, Graphics::Instance()->SCREEN_HEIGHT * 0.5));
}

bool Tank::IgnoreCollisions()
{
	return !mVisible || mAnimating;
}

void Tank::HandleTracks()
{
	if ((mVelocity.y > 1.0f || mVelocity.y < -1.0f) && Active())
	{
		if (!(rand() % 8))
			mParticles.push_back(new Particle(Pos(), Rotation()));
	}

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

void Tank::HandleMovement()
{
	//Simulate friction
	mVelocity *= 0.99f;
	mOrientation *= 0.99f;

	Translate(mVelocity * mTimer->DeltaTime(), local);
	Rotate(mOrientation);

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

void Tank::Visible(bool visible)
{
	mVisible = visible;
}

void Tank::Hit(PhysEntity* other)
{
	if (other->CollisionLayer() == CollisionLayers::HostileProjectiles)
	{
		mHealth--;
		mTank->Flash();
		mBarrel->Flash();

		if (mHealth < 1)
		{
			mAudio->PlaySFX("explode.wav");
			mDeathAnimation->ResetAnimation();
			mAnimating = true;
			mDead = true;
			Active(false);
		}
	}
	else
	{
		if (other->CollisionLayer() == CollisionLayers::Object)
		{
			if (static_cast<Tile*> (other)->Passable())
				return;
		}
		else if (other->CollisionLayer() == CollisionLayers::Hostile)
		{
			if (static_cast<Enemy*> (other)->Flying())
				return;
		}

		if (mColliders[0]->GetMTV().mValid)
		{
			if (Dot(Pos() - other->Pos(), mColliders[0]->GetMTV().mAxis) < 0.0f)
				Translate(-mColliders[0]->GetMTV().mOverlap * mColliders[0]->GetMTV().mAxis);
			else
				Translate(mColliders[0]->GetMTV().mOverlap * mColliders[0]->GetMTV().mAxis);
		}
	}
}

void Tank::Heal()
{
	mHealth = 4;
}

int Tank::Health()
{
	return mHealth;
}

bool Tank::Dead()
{
	return mAnimating ? false : mDead;
}

bool Tank::IsAnimating()
{
	return mAnimating;
}

void Tank::Accelerate(bool forward)
{
	//Apply forward acceleration
	if (forward)
	{
		mVelocity -= VEC2_UP * mAcceleration * mTimer->DeltaTime();
	}
	//Apply backward acceleration
	else
	{
		mVelocity += VEC2_UP * mAcceleration * 0.66f * mTimer->DeltaTime();
	}
}

void Tank::Turn(bool clockwise)
{
	//Add to rotation
	if (clockwise)
	{
		mOrientation += mRotationSpeed * mTimer->DeltaTime();
	}
	//Subtract from rotation
	else
	{
		mOrientation -= mRotationSpeed * mTimer->DeltaTime();
	}
}

void Tank::Aim(Vector2 pos)
{
	Vector2 direction = (Pos(GameEntity::world) - pos).Normalize();
	float angle = atan2(direction.y, direction.x) * RAD_TO_DEG;
	mBarrel->Rotation(angle + 90.0f - Rotation());
}

void Tank::Fire()
{
	if (mReloadTimer > 0)
		return;
	else if (Active())
	{
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

void Tank::Update()
{
	if (mAnimating)
	{
		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
		mVisible = mAnimating;
	}
	else
	{
		if (Active())
		{
			HandleMovement();
		}
	}

	if (mReloadTimer > 0)
	{
		mReloadTimer -= mTimer->DeltaTime();

		if (mReloadTimer < 0)
			mReloadTimer = 0;
	}

	for (auto &bullet : mBullets)
		bullet->Update();

	HandleTracks();
}

void Tank::Render()
{
	for (const auto &particle : mParticles)
		particle->Render();

	if (mVisible)
	{
		if (mAnimating)
		{
			mDeathAnimation->Render();
		}
		else
		{
			mTank->Render();
			mBarrel->Render();
		}
	}

	for (const auto &bullet : mBullets)
		bullet->Render();

	PhysEntity::Render();
}