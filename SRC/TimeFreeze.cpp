#include "TimeFreeze.h"
#include "Asteroids.h"
#include "GameSession.h"
#include <vector>

using namespace std;

TimeFreeze::TimeFreeze(const GLVector3f& pos, vector<shared_ptr<GameObject>>& asteroids) : PowerUp(pos, "TimeFreeze") {
	vec_astr = asteroids;
}


void TimeFreeze::applyEffect() {
	for (shared_ptr<GameObject> asteroid : vec_astr) {
		asteroid->SetVelocity(GLVector3f(0, 0, 0));
	}
}