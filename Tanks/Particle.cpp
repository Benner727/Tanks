#include "Particle.h"

Particle::Particle(Vector2 pos, float rotation)
{
	mTimer = Timer::Instance();

	mDead = false;

	mParticleLife = 0.5f + rand() % 10 / 10.0f;
	mParticleTimer = 0.0f;

	mTexture = new Texture("Player/tracksSmall.png", 0, 0, 37, 4);
	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);

	Pos(pos);
	Rotation(rotation);
}

Particle::~Particle()
{
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

bool Particle::Dead()
{
	return mDead;
}

void Particle::Update()
{
	mParticleTimer += mTimer->DeltaTime();

	if (mParticleTimer >= mParticleLife)
		mDead = true;
}

void Particle::Render()
{
	if (!mDead)
		mTexture->Render();
}