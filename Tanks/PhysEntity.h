#ifndef PHYSENTITY_H
#define PHYSENTITY_H

#include "Collider.h"
#include <vector>

class PhysEntity : public GameEntity
{
public:
	enum class CollisionLayers
	{
		Friendly = 0,
		FriendlyProjectiles,
		Hostile,
		HostileProjectiles,
		Object,

		MaxLayers
	};

	enum class CollisionFlags
	{
		None = 0x00,
		Friendly = 0x01,
		FriendlyProjectiles = 0x02,
		Hostile = 0x04,
		HostileProjectiles = 0x08,
		Object = 0x10,
	};

protected:
	unsigned long mId;
	CollisionLayers mCollisionLayer;

	std::vector<Collider*> mColliders;

	Collider* mBroadPhaseCollider;

	void AddCollider(Collider* collider, Vector2 localPos = VEC2_ZERO);

	virtual bool IgnoreCollisions();

public:
	PhysEntity();
	virtual ~PhysEntity();

	unsigned long Id();
	CollisionLayers CollisionLayer();

	bool CheckCollision(PhysEntity* other);

	std::vector<Collider*> GetCollider() const { return mColliders; }

	virtual void Hit(PhysEntity* other);

	virtual void Render();
};

inline PhysEntity::CollisionFlags operator|(PhysEntity::CollisionFlags a, PhysEntity::CollisionFlags b)
{
	return static_cast<PhysEntity::CollisionFlags>(static_cast<unsigned int> (a) | static_cast<unsigned int> (b));
}

inline PhysEntity::CollisionFlags operator&(PhysEntity::CollisionFlags a, PhysEntity::CollisionFlags b)
{
	return static_cast<PhysEntity::CollisionFlags>(static_cast<unsigned int> (a) & static_cast<unsigned int> (b));
}

#endif