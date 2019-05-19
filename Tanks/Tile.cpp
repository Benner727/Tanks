#include "Tile.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "PhysicsManager.h"

Tile::Tile(Texture* tex, Vector2 pos, bool passable, bool shootable)
{
	Pos(pos);

	mTexture = tex;
	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);

	mPassable = passable;
	mShootable = shootable;

	mCollisionLayer = PhysEntity::CollisionLayers::Object;

	AddCollider(new BoxCollider(mTexture->ScaledDimensions() * 0.85f));

	mId = PhysicsManager::Instance()->RegisterEntity(this, mCollisionLayer);
}


Tile::~Tile()
{
	delete mTexture;
	mTexture = nullptr;
}

void Tile::Hit(PhysEntity* other)
{

}

void Tile::Update()
{

}

void Tile::Render()
{
	mTexture->Render();

	PhysEntity::Render();
}