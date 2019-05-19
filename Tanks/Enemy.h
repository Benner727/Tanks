#ifndef ENEMY_H
#define ENEMY_H

#include "PhysEntity.h"
#include "AnimatedTexture.h"
#include "Bullet.h"
#include "Particle.h"
#include "AudioManager.h"

class Enemy : public PhysEntity
{
public:
	enum STATES { spawning, alive, dead };

protected:
	Timer* mTimer;
	AudioManager* mAudio;

	Texture *mTank;
	Texture* mBarrel;
	AnimatedTexture *mDeathAnimation;

	int mValue;

	float mReloadTimer;
	float mFireRate;
	std::vector<Bullet*> mBullets;

	float mPosTimer;
	float mPosDelay;
	float mAngle;

	GameEntity* mTarget;

	STATES mCurrentState;

	float mAcceleration;
	float mRotationSpeed;

	float mSpawnTimer;
	bool mSpawned;
	bool mAnimating;
	bool mDead;

	float mHitCounter;
	bool mFlying;

	std::vector<Particle*> mParticles;
	virtual void HandleTracks();

	virtual void HandleSpawning();
	virtual void HandleLiving();
	virtual void HandleDeath();

private:
	bool IgnoreCollisions() override;

public:
	Enemy();
	virtual ~Enemy();

	void Target(GameEntity* target);

	void HandleStates();

	bool IsAnimating();

	bool Flying() { return mFlying; }

	void Hit(PhysEntity* other) override;
	bool Dead();

	int Value() const { return mValue; }

	void Update();
	void Render();
};

#endif