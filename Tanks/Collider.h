#ifndef COLLIDER_H
#define COLLIDER_H

#include "Texture.h"

class Collider : public GameEntity
{
public:
	enum class ColliderType 
	{
		Box,
		Circle
	};

	struct MTV {
		MTV() {};

		MTV(Vector2 axis, float overlap, bool valid)
		{
			mValid = valid;
			mOverlap = overlap;
			mAxis = axis;
		};

		bool mValid;
		Vector2 mAxis;
		float mOverlap;
	};

protected:
	ColliderType mType;

	MTV mMTV;

	static const bool DEBUG_COLLIDERS = false;
	Texture* mDebugTexture;

	void SetDebugTexture(Texture* texture);
public:
	Collider(ColliderType type);
	virtual ~Collider();

	virtual Vector2 GetFurthestPoint() = 0;

	ColliderType GetType();
	
	MTV GetMTV() { return mMTV; }
	void SetMTV(MTV mtv) { mMTV = mtv; }

	virtual void Render();
};

#endif