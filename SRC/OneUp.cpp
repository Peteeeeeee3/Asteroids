#include "OneUp.h"

OneUp::OneUp(shared_ptr<Player> player, GLVector3f pos) : PowerUp(pos, "Oneup") {
	this->player = player;
}