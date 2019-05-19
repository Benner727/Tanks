#include "Bullet.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
#include "Tile.h"

Bullet::Bullet(bool friendly, int size)
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mSpeed = 600.0f;
	mStartPos = VEC2_ZERO;
	mDistance = 500.0f;

	mDeathAnimation = new AnimatedTexture("Player/smoke.png", 0, 0, 64, 63, 5, 1.0f, AnimatedTexture::horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Pos(VEC2_ZERO);
	mDeathAnimation->Scale(Vector2(0.33f, 0.33f));
	mDeathAnimation->WrapMode(AnimatedTexture::once);

	if (friendly)
	{
		switch (size)
		{
		case 0:
			mTexture = new Texture("Player/bulletRed2_outline.png");
			mFlash = new Texture("Player/shotRed.png");
			break;
		default:
			mTexture = new Texture("PlayerbulletRed2_outline.png");
			mFlash = new Texture("Player/shotRed.png");
		}

		mCollisionLayer = PhysEntity::CollisionLayers::FriendlyProjectiles;
	}
	else
	{
		switch (size)
		{
		case 0:
			mTexture = new Texture("Player/bulletDark2_outline.png");
			mFlash = new Texture("Player/shotRed.png");

			mSpeed = 500.0f;
			break;
		case 1:
			mTexture = new Texture("Player/bulletDark2_outline.png");
			mTexture->Scale(Vector2(1.25f, 1.25f));

			mFlash = new Texture("Player/shotRed.png");
			mFlash->Scale(Vector2(1.25f, 1.25f));

			mDeathAnimation->Scale(Vector2(0.5f, 0.5f));

			mSpeed = 700.0f;
			break;
		case 2:
			mTexture = new Texture("Player/bulletDark1_outline.png");
			mFlash = new Texture("Player/shotThin.png");
			
			mDeathAnimation->Scale(Vector2(0.33f, 0.33f));
			
			mSpeed = 300.0f;
			break;
		default:
			mTexture = new Texture("Player/bulletDark2_outline.png");
			mFlash = new Texture("Player/shotRed.png");
			mSpeed = 500.0f;
		}

		mCollisionLayer = PhysEntity::CollisionLayers::HostileProjectiles;
	}

	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);

	mFlash->Parent(this);
	mFlash->Pos(VEC2_ZERO);

	mFlashTimer = 0.0f;
	mFlashLength = 0.09f;

	Reload();

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);

	mOtherId = -1;
}

Bullet::~Bullet()
{
	mTimer = nullptr;
	mAudio = nullptr;

	delete mTexture;
	mTexture = nullptr;

	delete mFlash;
	mFlash = nullptr;
}

void Bullet::Fire(Vector2 pos, float rotation)
{
	Pos(pos);
	Rotation(rotation + rand() % 6 - 2.5f);
	Translate(VEC2_UP * mFlash->ScaledDimensions().y * 0.75f, local);
	mStartPos = Pos();
	Active(true);
	mVisible = true;
	mFlashTimer = mFlashLength;
	mDistance = mSpeed * 0.66f + rand() % 200;
}

void Bullet::Reload()
{
	mFlashTimer = 0.0f;
	mVisible = false;
	mAnimating = false;
	Active(false);
	Pos(VEC2_ZERO);
	mOtherId = -1;
}

void Bullet::Hit(PhysEntity* other)
{
	if (Active())
	{
		if (other->CollisionLayer() == PhysEntity::CollisionLayers::Object)
		{
			if (static_cast<Tile*> (other)->Shootable())
				return;
		}
		else if (other->CollisionLayer() == PhysEntity::CollisionLayers::HostileProjectiles)
		{
			if (!static_cast<Bullet*>(other)->Active() && Id() != static_cast<Bullet*>(other)->OtherId())
				return;
			else
			{
				Pos(Vector2((Pos().x + other->Pos().x) / 2.0f, (Pos().y + other->Pos().y) / 2.0f));
				mOtherId = other->Id();
			}
		}
		else if (other->CollisionLayer() == PhysEntity::CollisionLayers::FriendlyProjectiles)
		{
			if (!static_cast<Bullet*>(other)->Active() && Id() != static_cast<Bullet*>(other)->OtherId())
				return;
			else
			{
				Reload();
				return;
			}
		}

		mAudio->PlaySFX("muffled.wav", 0, 5);
		mDeathAnimation->ResetAnimation();
		mAnimating = true;
		Active(false);
	}
}

bool Bullet::IgnoreCollisions()
{
	return !Active();
}

void Bullet::Update()
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
			Translate(VEC2_UP * mSpeed * mTimer->DeltaTime(), local);

			if (Pos().x < 0.0f || Pos().x > Graphics::SCREEN_WIDTH)
				Reload();
			else if (Pos().y < 0.0f || Pos().y > Graphics::SCREEN_HEIGHT)
				Reload();
			else if ((mStartPos - Pos()).Magnitude() > mDistance)
			{
				mAudio->PlaySFX("muffled.wav", 0, 5);
				mDeathAnimation->ResetAnimation();
				mAnimating = true;
				Active(false);
			}

			if (mFlashTimer > 0.0f)
				mFlashTimer -= mTimer->DeltaTime();
		}
		else
			Reload();
	}
}

void Bullet::Render()
{
	if (mVisible)
	{
		if (mAnimating)
		{
			mDeathAnimation->Render();
		}
		else if (mFlashTimer > 0.0f)
			mFlash->Render();
		else
			mTexture->Render();
	}

	PhysEntity::Render();
}