#ifndef __ONEUP_H__
#define __ONEUP_H__

#include "PowerUp.h"
#include "GameObject.h"
#include "Player.h"

class OneUp : public PowerUp {
private:
	shared_ptr<Player> player;

public:
	OneUp() {}
	OneUp(shared_ptr<Player> player, GLVector3f pos);
	~OneUp() {}
	void applyEffect() {}
};

#endif // !__ONEUP_H__