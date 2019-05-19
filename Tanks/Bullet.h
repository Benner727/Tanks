#ifndef BULLET_H
#define BULLET_H

#include "PhysEntity.h"
#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "Timer.h"

class Bullet : public PhysEntity
{
private:
	Timer *mTimer;
	AudioManager *mAudio;

	float mSpeed;

	Texture* mTexture;

	bool  mVisible;
	bool mAnimating;
	AnimatedTexture* mDeathAnimation;

	Texture* mFlash;
	float mFlashTimer;
	float mFlashLength;

	Vector2 mStartPos;
	float mDistance;

	unsigned long mOtherId;

	bool IgnoreCollisions() override;

public:
	Bullet(bool friendly = true, int type = 0);
	~Bullet();

	void Fire(Vector2 pos, float rotation);
	void Reload();

	void Hit(PhysEntity* other) override;

	unsigned long OtherId() { return mOtherId; }

	bool Animating() { return mAnimating; }

	void Update();
	void Render();
};

#endif