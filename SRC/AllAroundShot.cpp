#include "AllAroundShot.h"

AllAroundShot::AllAroundShot(shared_ptr<GameObject> spaceship, GLVector3f pos) : PowerUp(pos, "AAShot"){
	ss = dynamic_pointer_cast<Spaceship>(spaceship);
}

void AllAroundShot::applyEffect() {
	ss->Shoot360();
}