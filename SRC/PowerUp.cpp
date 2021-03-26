#include "PowerUp.h"
#include "GameObject.h"
#include "BoundingSphere.h"
#include "BoundingShape.h"

//Default Constructor
PowerUp::PowerUp() : GameObject("Powerup") {
}

//Constructor with given position
PowerUp::PowerUp(const GLVector3f& pos, char const* const type) : GameObject(type) 
{
	mAngle = rand() % 360;
	mRotation = 0; // rand() % 90;
	mPosition.x = pos.x;
	mPosition.y = pos.y;
	mPosition.z = 0.0;
	mVelocity.x = 14.0 * cos(DEG2RAD * mAngle);
	mVelocity.y = 14.0 * sin(DEG2RAD * mAngle);
	mVelocity.z = 0.0;
}

//Destructor
PowerUp::~PowerUp() {}

//test to seem if collided with 
bool PowerUp::CollisionTest(shared_ptr<GameObject> o) {
	if (o->GetType() != GameObjectType("Spaceship")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void PowerUp::OnCollision(const GameObjectList& objects) {
	mWorld->FlagForRemoval(GetThisPtr());
}