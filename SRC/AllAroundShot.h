#ifndef __ALLAROUNDSHOT_H__
#define __ALLAROUNDSHOT_H__

#include "PowerUp.h"
#include "Spaceship.h"

class AllAroundShot : public PowerUp {
private:
	shared_ptr<Spaceship> ss;

public:
	AllAroundShot() {}
	AllAroundShot(shared_ptr<GameObject> spaceship, GLVector3f pos);
	~AllAroundShot() {}
	void applyEffect();
};

#endif // !__ALLAROUNDSHOT_H__
