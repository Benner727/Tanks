#ifndef TANK_H
#define TANK_H

#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "Bullet.h"
#include "Particle.h"

class Tank : public PhysEntity
{
private:
	Timer* mTimer;
	AudioManager* mAudio;

	bool  mVisible;
	bool mDead;
	bool mAnimating;

	int mHealth;

	Texture *mTank;
	Texture* mBarrel;

	AnimatedTexture* mDeathAnimation;

	float mReloadTimer;
	float mFireRate;
	std::vector<Bullet*> mBullets;

	float mAcceleration;
	float mOrientation;
	float mRotationSpeed;

	Vector2 mVelocity;

	std::vector<Particle*> mParticles;

	bool IgnoreCollisions() override;

	void HandleTracks();
	void HandleMovement();

public:
	Tank();
	~Tank();

	void Reset();

	void Visible(bool visible);

	void Hit(PhysEntity* other) override;
	
	void Heal();
	int Health();
	bool Dead();

	bool IsAnimating();

	void Accelerate(bool forward);
	void Turn(bool clockwise);
	void Aim(Vector2 pos);
	void Fire();

	void Update();
	void Render();
};

#endif