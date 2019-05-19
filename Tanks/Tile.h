#ifndef TILE_H
#define TILE_H

#include "Texture.h"
#include "PhysEntity.h"

class Tile : public PhysEntity
{
private:
	Texture *mTexture;

	bool mPassable;
	bool mShootable;

public:
	Tile(Texture* tex, Vector2 pos = VEC2_ZERO, bool passable = false, bool shootable = false);
	~Tile();

	void Hit(PhysEntity* other) override;

	bool Passable() { return mPassable; }
	bool Shootable() { return mShootable; }

	void Update();
	void Render();
};

#endif