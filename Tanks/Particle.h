#ifndef PARTICLE_H
#define PARTICLE_H

#include "Texture.h"
#include "Timer.h"

class Particle : public GameEntity
{
public:
	Particle(Vector2 pos, float rotation);
	~Particle();

private:
	Timer* mTimer;

	Texture* mTexture;

	float mParticleLife;
	float mParticleTimer;

	bool mDead;

public:
	bool Dead();

	void Update();
	void Render();
};

#endif