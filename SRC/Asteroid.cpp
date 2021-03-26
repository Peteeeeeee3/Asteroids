#include <stdlib.h>
#include "GameUtil.h"
#include "Asteroid.h"
#include "BoundingShape.h"
#include "Asteroids.h"

Asteroid::Asteroid(void) : GameObject("Asteroid") 
{
	isChildSpawn = false;
	mAngle = rand() % 360;
	mRotation = 0; // rand() % 90;
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
	mPosition.z = 0.0;
	mVelocity.x = 10.0 * cos(DEG2RAD*mAngle);
	mVelocity.y = 10.0 * sin(DEG2RAD*mAngle);
	mVelocity.z = 0.0;
}

Asteroid::Asteroid(const bool& _isChildSpawn, const GLVector3f& pos) : GameObject("Asteroid")
{
	isChildSpawn = _isChildSpawn;
	mAngle = rand() % 360;
	mRotation = 0; // rand() % 90;
	mPosition.x = pos.x;
	mPosition.y = pos.y;
	mPosition.z = 0.0;
	mVelocity.x = 15.0 * cos(DEG2RAD * mAngle);
	mVelocity.y = 15.0 * sin(DEG2RAD * mAngle);
	mVelocity.z = 0.0;
}

Asteroid::~Asteroid(void)
{
}

bool Asteroid::CollisionTest(shared_ptr<GameObject> o)
{
	if (GetType() == o->GetType()) return false;
	if (o->GetType() == GameObjectType("TimeFreeze")) return false;
	if (o->GetType() == GameObjectType("Lazer")) return false;
	if (o->GetType() == GameObjectType("3shot")) return false;
	if (o->GetType() == GameObjectType("AAShot")) return false;
	if (o->GetType() == GameObjectType("Oneup")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Asteroid::OnCollision(const GameObjectList& objects)
{
	mWorld->FlagForRemoval(GetThisPtr());
}
