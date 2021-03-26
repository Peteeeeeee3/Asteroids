#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "GameObject.h"
//#include "Spaceship.h"

class PowerUp : public GameObject {
private:
	shared_ptr<Shape> mPowerupShape;
public:
	PowerUp();
	PowerUp(const GLVector3f& pos, char const* const type);
	~PowerUp();

	virtual void applyEffect() = 0;
	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);
	void setPowerUpShape(shared_ptr<Shape> powerup_shape) { mPowerupShape = powerup_shape; }
};

#endif