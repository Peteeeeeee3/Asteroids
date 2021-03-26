#include "3shot.h"
#include "Spaceship.h"

Trishot::Trishot(shared_ptr<GameObject> spaceship, GLVector3f pos) : PowerUp(pos, "3shot") {
	ss = dynamic_pointer_cast<Spaceship>(spaceship);
}

void Trishot::applyEffect() {
 	ss->Shoot3();
}