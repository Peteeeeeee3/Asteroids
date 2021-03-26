#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "GameObject.h"
#include "GameUtil.h"

class Asteroid : public GameObject
{
private:
	bool isChildSpawn; //records whether an astroid is an original or one created upon destruction of an asteroid
public:
	Asteroid(void);
	Asteroid(const bool& _isChildSpawn, const GLVector3f& pos);
	~Asteroid(void);

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);
	bool getIsChildSpawn() { return isChildSpawn; }
};

#endif
