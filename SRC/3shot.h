#ifndef __3SHOT_H__
#define __3SHOT_H__

#include "PowerUp.h"
#include "GameObject.h"
#include "Spaceship.h"

class Trishot : public PowerUp
{
private:
	shared_ptr<Spaceship> ss;
public:
	Trishot() {}
	Trishot(shared_ptr<GameObject> spaceship, GLVector3f pos);
	~Trishot() {}
	void applyEffect();
};

#endif // !__3SHOT_H__
