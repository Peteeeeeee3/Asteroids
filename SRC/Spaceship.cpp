#include "GameUtil.h"
#include "GameWorld.h"
#include "Bullet.h"
#include "Spaceship.h"
#include "BoundingSphere.h"
#include "Asteroids.h"
#include "TimeFreeze.h"
#include "AnimationManager.h"
#include "Animation.h"

using namespace std;

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/**  Default constructor. */
Spaceship::Spaceship()
	: GameObject("Spaceship"), mThrust(0)
{
}

/** Construct a spaceship with given position, velocity, acceleration, angle, and rotation. */
Spaceship::Spaceship(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r)
	: GameObject("Spaceship", p, v, a, h, r), mThrust(0)
{
}

/** Copy constructor. */
Spaceship::Spaceship(const Spaceship& s)
	: GameObject(s), mThrust(0)
{
}

/** Destructor. */
Spaceship::~Spaceship(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Update this spaceship. */
void Spaceship::Update(int t)
{
	// Call parent update function
	GameObject::Update(t);
}

/** Render this spaceship. */
void Spaceship::Render(void)
{
	if (mSpaceshipShape.get() != NULL) mSpaceshipShape->Render();

	// If ship is thrusting
	if ((mThrust > 0) && (mThrusterShape.get() != NULL)) {
		mThrusterShape->Render();
	}

	GameObject::Render();
}

/** Fire the rockets. */
void Spaceship::Thrust(float t)
{
	mThrust = t;
	// Increase acceleration in the direction of ship
	mAcceleration.x = mThrust*cos(DEG2RAD*mAngle);
	mAcceleration.y = mThrust*sin(DEG2RAD*mAngle);
}

/** Set the rotation. */
void Spaceship::Rotate(float r)
{
	mRotation = r;
}

/** Shoot a bullet. */
void Spaceship::Shoot(void)
{
	// Check the world exists
	if (!mWorld) return;
	// Construct a unit length vector in the direction the spaceship is headed
	GLVector3f spaceship_heading(cos(DEG2RAD*mAngle), sin(DEG2RAD*mAngle), 0);
	spaceship_heading.normalize();
	// Calculate the point at the node of the spaceship from position and heading
	GLVector3f bullet_position = mPosition + (spaceship_heading * 4);
	// Calculate how fast the bullet should travel
	float bullet_speed = 30;
	// Construct a vector for the bullet's velocity
	GLVector3f bullet_velocity = mVelocity + spaceship_heading * bullet_speed;
	// Construct a new bullet
	shared_ptr<GameObject> bullet
		(new Bullet(bullet_position, bullet_velocity, mAcceleration, mAngle, 0, 2000, false));
	bullet->SetBoundingShape(make_shared<BoundingSphere>(bullet->GetThisPtr(), 2.0f));
	bullet->SetShape(mBulletShape);
	// Add the new bullet to the game world
	mWorld->AddObject(bullet);

}

void Spaceship::fireLazer(void) {
	// Check the world exists
	if (!mWorld) return;
	//sprite for lazer
	Animation* explosion_anim = AnimationManager::GetInstance().CreateAnimationFromFile("lazer", 421, 77, 421, 77, "green_laser.png");
	// Construct a unit length vector in the direction the spaceship is headed
	Animation* anim_ptr = AnimationManager::GetInstance().GetAnimationByName("lazer");
	shared_ptr<Sprite> lazer_sprite = make_shared<Sprite>(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
	lazer_sprite->SetLoopAnimation(true);
	GLVector3f spaceship_heading(cos(DEG2RAD * mAngle), sin(DEG2RAD * mAngle), 0);
	spaceship_heading.normalize();
	// Calculate the point at the node of the spaceship from position and heading
	GLVector3f bullet_position = mPosition + (spaceship_heading * 20);
	// Calculate how fast the bullet should travel
	float bullet_speed = 40;
	// Construct a vector for the bullet's velocity
	GLVector3f bullet_velocity = mVelocity + spaceship_heading * bullet_speed;
	// Construct a new bullet
	shared_ptr<GameObject> laser
		(new Bullet(bullet_position, bullet_velocity, mAcceleration, mAngle, 0, 4000, true));
	laser->SetBoundingShape(make_shared<BoundingSphere>(laser->GetThisPtr(), 20.0f));
	laser->SetSprite(lazer_sprite);
	laser->SetScale(0.1f);
	// Add the new bullet to the game world
	mWorld->AddObject(laser);
}

void Spaceship::Shoot3(void) {
	// Check the world exists
	if (!mWorld) return;
	for (int i = 1; i < 4; ++i) {
		//sprite for lazer
		Animation* explosion_anim = AnimationManager::GetInstance().CreateAnimationFromFile("lazer", 421, 76, 421, 76, "red_laser.png");
		// Construct a unit length vector in the direction the spaceship is headed
		Animation* anim_ptr = AnimationManager::GetInstance().GetAnimationByName("lazer");
		shared_ptr<Sprite> lazer_sprite = make_shared<Sprite>(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
		lazer_sprite->SetLoopAnimation(true);
		GLVector3f spaceship_heading(cos(DEG2RAD * mAngle), sin(DEG2RAD * mAngle), 0);
		spaceship_heading.normalize();
		// Calculate the point at the node of the spaceship from position and heading
		GLVector3f bullet_position = mPosition - GLVector3f(10, 0, 0) + GLVector3f(10 * i, 0, 0) + (spaceship_heading * 20) ;
		// Calculate how fast the bullet should travel
		float bullet_speed = 40;
		// Construct a vector for the bullet's velocity
		GLVector3f bullet_velocity = mVelocity + spaceship_heading * bullet_speed;
		// Construct a new bullet
		shared_ptr<GameObject> laser
		(new Bullet(bullet_position, bullet_velocity, mAcceleration, mAngle, 0, 4000, true));
		laser->SetBoundingShape(make_shared<BoundingSphere>(laser->GetThisPtr(), 20.0f));
		laser->SetSprite(lazer_sprite);
		laser->SetScale(0.05f);
		// Add the new bullet to the game world
		mWorld->AddObject(laser);
	}
}

void Spaceship::Shoot360(void) {
	// Check the world exists
	if (!mWorld) return;
	for (int i = 1; i < 90; ++i) {
		// Construct a unit length vector in the direction the spaceship is headed
		GLVector3f spaceship_heading(cos(DEG2RAD * mAngle), sin(DEG2RAD * mAngle), 0);
		spaceship_heading.normalize();
		// Calculate the point at the node of the spaceship from position and heading
		GLVector3f bullet_position = mPosition + (spaceship_heading * 4);
		// Calculate how fast the bullet should travel
		float bullet_speed = 30;
		// Construct a vector for the bullet's velocity
		GLVector3f bullet_velocity = mVelocity + spaceship_heading * bullet_speed;
		mAngle += 4;
		// Construct a new bullet
		shared_ptr<GameObject> bullet
		(new Bullet(bullet_position, bullet_velocity, mAcceleration, mAngle, 0, 2000, false));
		bullet->SetBoundingShape(make_shared<BoundingSphere>(bullet->GetThisPtr(), 2.0f));
		bullet->SetShape(mBulletShape);
		// Add the new bullet to the game world
		mWorld->AddObject(bullet);
	}
}

bool Spaceship::CollisionTest(shared_ptr<GameObject> o)
{
	if (o->GetType() != GameObjectType("Asteroid")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Spaceship::OnCollision(const GameObjectList &objects)
{
	mWorld->FlagForRemoval(GetThisPtr());
}
/*
void Spaceship::SetPowerUp(GameObject powerup) {
		mPowerUp = make_shared<GameObject>(powerup);
}

void Spaceship::UsePowerUp() {
	dynamic_pointer_cast<TimeFreeze>(mPowerUp)->applyEffect();
	mPowerUp.reset();
}
*/