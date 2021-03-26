#ifndef __TIMEFREEZE_H__
#define __TIMEFREEZE_H__

#include "PowerUp.h"
#include "Spaceship.h"
#include "GameObject.h"
#include "Asteroids.h"
#include <vector>

class TimeFreeze : public PowerUp {
private:
	vector<shared_ptr<GameObject>> vec_astr;

public:
	TimeFreeze(const GLVector3f& pos, vector<shared_ptr<GameObject>>& asteroids);
	~TimeFreeze() {}
	void applyEffect();
};

#endif // !_TIMEFREEZE__