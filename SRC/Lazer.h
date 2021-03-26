#ifndef __LAZER_H__
#define	__LAZER_H__

#include "PowerUp.h"
#include "Spaceship.h"

class Lazer : public PowerUp {
private:
	shared_ptr<Spaceship> ss;

public:
	Lazer(void) {}
	Lazer(shared_ptr<GameObject> spaceship, GLVector3f pos);
	void applyEffect(void);
	~Lazer(void) {}
};

#endif // !__LAZER_H__
