#include "Lazer.h"
#include "PowerUp.h"
#include "GameObject.h"

Lazer::Lazer(shared_ptr<GameObject> spaceship, GLVector3f pos) : PowerUp(pos, "Lazer") {
	ss = dynamic_pointer_cast<Spaceship>(spaceship);
}

void Lazer::applyEffect(void) {
	//call fireLazer function
	ss->fireLazer();
}