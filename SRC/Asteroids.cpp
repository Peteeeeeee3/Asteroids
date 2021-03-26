#include "Asteroid.h"
#include "Asteroids.h"
#include "Animation.h"
#include "AnimationManager.h"
#include "GameUtil.h"
#include "GameWindow.h"
#include "GameWorld.h"
#include "GameDisplay.h"
#include "Spaceship.h"
#include "BoundingShape.h"
#include "BoundingSphere.h"
#include "GUILabel.h"
#include "Explosion.h"
#include "PowerUp.h"
#include "TimeFreeze.h"
#include "Lazer.h"
#include "3shot.h"
#include "AllAroundShot.h"
#include "OneUp.h"

#include <string>


// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/** Constructor. Takes arguments from command line, just in case. */
Asteroids::Asteroids(int argc, char *argv[])
	: GameSession(argc, argv)
{
	mLevel = 0;
	mAsteroidCount = 0;

	mMiniSpawnCount = 3;
}

/** Destructor. */
Asteroids::~Asteroids(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Start an asteroids game. */
void Asteroids::Start()
{
	// Create a shared pointer for the Asteroids game object - DO NOT REMOVE
	shared_ptr<Asteroids> thisPtr = shared_ptr<Asteroids>(this);

	// Add this class as a listener of the game world
	mGameWorld->AddListener(thisPtr.get());

	// Add this as a listener to the world and the keyboard
	mGameWindow->AddKeyboardListener(thisPtr);

	// Add a score keeper to the game world
	mGameWorld->AddListener(&mScoreKeeper);

// Add this class as a listener of the score keeper
mScoreKeeper.AddListener(thisPtr);

// Create an ambient light to show sprite textures
GLfloat ambient_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
glEnable(GL_LIGHT0);

Animation* explosion_anim = AnimationManager::GetInstance().CreateAnimationFromFile("explosion", 64, 1024, 64, 64, "explosion_fs.png");
Animation* asteroid1_anim = AnimationManager::GetInstance().CreateAnimationFromFile("asteroid1", 128, 8192, 128, 128, "asteroid1_fs.png");
Animation* asteroid2_anim = AnimationManager::GetInstance().CreateAnimationFromFile("asteroid2", 128, 8192, 128, 128, "asteroid2_fs.png");
Animation* asteroid3_anim = AnimationManager::GetInstance().CreateAnimationFromFile("asteroid3", 64, 4096, 64, 64, "asteroid3_fs.png");
Animation* spaceship_anim = AnimationManager::GetInstance().CreateAnimationFromFile("spaceship", 128, 128, 128, 128, "spaceship_fs.png");
Animation* powerup1_anim = AnimationManager::GetInstance().CreateAnimationFromFile("powerup_blue", 32, 256, 32, 32, "crystal-qubodup-ccby3-32-blue.png");
Animation* powerup2_anim = AnimationManager::GetInstance().CreateAnimationFromFile("powerup_green", 32, 256, 32, 32, "crystal-qubodup-ccby3-32-green.png");
Animation* powerup3_anim = AnimationManager::GetInstance().CreateAnimationFromFile("powerup_orange", 32, 256, 32, 32, "crystal-qubodup-ccby3-32-orange.png");
Animation* powerup4_anim = AnimationManager::GetInstance().CreateAnimationFromFile("powerup_black", 32, 256, 32, 32, "crystal-qubodup-ccby3-32-grey.png");
Animation* powerup5_anim = AnimationManager::GetInstance().CreateAnimationFromFile("powerup_yellow", 32, 256, 32, 32, "crystal-qubodup-ccby3-32-yellow.png");

// Create a spaceship and add it to the world
mGameWorld->AddObject(CreateSpaceship());
// Create some asteroids and add them to the world
CreateAsteroids(10, false, GLVector3f());

//Create the GUI
CreateGUI();

// Add a player (watcher) to the game world
mGameWorld->AddListener(&mPlayer);

// Add this class as a listener of the player
mPlayer.AddListener(thisPtr);

// Start the game
GameSession::Start();
}

/** Stop the current game. */
void Asteroids::Stop()
{
	// Stop the game
	GameSession::Stop();
}

// PUBLIC INSTANCE METHODS IMPLEMENTING IKeyboardListener /////////////////////

void Asteroids::OnKeyPressed(uchar key, int x, int y)
{
	switch (key)
	{
	case ' ':
		mSpaceship->Shoot();
		break;
	/*case 'm':
		if (mSpaceship->GetMPowerUp() != nullptr) {
			OnPowerUpChange(dynamic_pointer_cast<PowerUp>(mSpaceship->GetMPowerUp()));
			mSpaceship->UsePowerUp();
		}*/
	default:
		break;
	}
}

void Asteroids::OnKeyReleased(uchar key, int x, int y) {}

void Asteroids::OnSpecialKeyPressed(int key, int x, int y)
{
	switch (key)
	{
		// If up arrow key is pressed start applying forward thrust
	case GLUT_KEY_UP: mSpaceship->Thrust(10); break;
		// If left arrow key is pressed start rotating anti-clockwise
	case GLUT_KEY_LEFT: mSpaceship->Rotate(90); break;
		// If right arrow key is pressed start rotating clockwise
	case GLUT_KEY_RIGHT: mSpaceship->Rotate(-90); break;
		// Default case - do nothing
	default: break;
	}
}

void Asteroids::OnSpecialKeyReleased(int key, int x, int y)
{
	switch (key)
	{
		// If up arrow key is released stop applying forward thrust
	case GLUT_KEY_UP: mSpaceship->Thrust(0); break;
		// If left arrow key is released stop rotating
	case GLUT_KEY_LEFT: mSpaceship->Rotate(0); break;
		// If right arrow key is released stop rotating
	case GLUT_KEY_RIGHT: mSpaceship->Rotate(0); break;
		// Default case - do nothing
	default: break;
	}
}

// PUBLIC INSTANCE METHODS IMPLEMENTING IGameWorldListener ////////////////////

void Asteroids::OnObjectRemoved(GameWorld* world, shared_ptr<GameObject> object)
{
	OnHealthChange(mPlayer.GetLives());
 	if (object->GetType() == GameObjectType("Asteroid"))
	{
		//remove form asteroids vector
   		for (auto astrd = mAsteroids.begin(); astrd != mAsteroids.end(); ++astrd) {
			if (*astrd == object) {
				mAsteroids.erase(astrd);
				break;
			}
		}
  		/*if () {
			if (mPowerUp->GetType() == GameObjectType("TimeFreeze")) {
				if (dynamic_pointer_cast<TimeFreeze>(mPowerUp)->GetActive()) {
					dynamic_pointer_cast<TimeFreeze>(mPowerUp)->incDstrd();
					if (dynamic_pointer_cast<TimeFreeze>(mPowerUp)->enoughDestroyed()) {
						dynamic_pointer_cast<TimeFreeze>(mPowerUp)->removeEffect();
						mPowerUp.reset();
						OnPowerUpChange(mPowerUp);
					}
				}
			}
		}*/


		
		//store the position of the asteroid
		GLVector3f position;
		position.x = object->GetPosition().x;
		position.y = object->GetPosition().y;

		shared_ptr<GameObject> explosion = CreateExplosion();
		explosion->SetPosition(object->GetPosition());
		explosion->SetRotation(object->GetRotation());
		mGameWorld->AddObject(explosion);
		mAsteroidCount--;
		//check whether it is an original asteroid or a mini
 		if (!dynamic_cast<Asteroid*>(object.get())->getIsChildSpawn()) 
		{
			//create further Asteroids when a big one is destroid
			CreateAsteroids(mMiniSpawnCount, true, position);
		}
		//create a powerup
		int random = rand();
		if (rand() % (5 * (mLevel + 1)) == 0) {
			CreatePowerUp(position);
		}
		

		//onAstroidNumChange(mAsteroidCount);
		//check to start level only after checked for small asteroid spawn
		if (mAsteroidCount <= 0)
		{
			SetTimer(500, START_NEXT_LEVEL);
		}
		position.~GLVector3();
	}

	if (object->GetType() == GameObjectType("TimeFreeze")) {
		static_pointer_cast<TimeFreeze>(object)->applyEffect();
	}
	else if (object->GetType() == GameObjectType("Lazer")) {
		dynamic_pointer_cast<Lazer>(object)->applyEffect();
	}
	else if (object->GetType() == GameObjectType("3shot")) {
		dynamic_pointer_cast<Trishot>(object)->applyEffect();
	}
	else if (object->GetType() == GameObjectType("AAShot")) {
		dynamic_pointer_cast<AllAroundShot>(object)->applyEffect();
	}
}

// PUBLIC INSTANCE METHODS IMPLEMENTING ITimerListener ////////////////////////

void Asteroids::OnTimer(int value)
{
	if (value == CREATE_NEW_PLAYER)
	{
		mSpaceship->Reset();
		mGameWorld->AddObject(mSpaceship);
	}

	if (value == START_NEXT_LEVEL)
	{
		mLevel++;
		int num_asteroids = 10 + 2 * mLevel;
		CreateAsteroids(num_asteroids, false, GLVector3f());
	}

	if (value == SHOW_GAME_OVER)
	{
		mGameOverLabel->SetVisible(true);
	}

}

// PROTECTED INSTANCE METHODS /////////////////////////////////////////////////
shared_ptr<GameObject> Asteroids::CreateSpaceship()
{
	// Create a raw pointer to a spaceship that can be converted to
	// shared_ptrs of different types because GameWorld implements IRefCount
	mSpaceship = make_shared<Spaceship>();
	mSpaceship->SetBoundingShape(make_shared<BoundingSphere>(mSpaceship->GetThisPtr(), 4.0f));
	shared_ptr<Shape> bullet_shape = make_shared<Shape>("bullet.shape");
	mSpaceship->SetBulletShape(bullet_shape);
	Animation *anim_ptr = AnimationManager::GetInstance().GetAnimationByName("spaceship");
	shared_ptr<Sprite> spaceship_sprite =
		make_shared<Sprite>(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
	mSpaceship->SetSprite(spaceship_sprite);
	mSpaceship->SetScale(0.1f);
	// Reset spaceship back to centre of the world
	mSpaceship->Reset();
	// Return the spaceship so it can be added to the world
	return mSpaceship;

}

void Asteroids::CreatePowerUp(const GLVector3f& pos)
{
	int rnd = rand() % 5;
	if (rnd == 0) {
		Animation* anim_ptr = AnimationManager::GetInstance().GetAnimationByName("powerup_blue");
		shared_ptr<Sprite> powerup_sprite = make_shared<Sprite>(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
		powerup_sprite->SetLoopAnimation(true);
		shared_ptr<TimeFreeze> powerup = make_shared<TimeFreeze>(pos, this->GetMAsteroids());
		powerup->SetBoundingShape(make_shared<BoundingSphere>(powerup->GetThisPtr(), 10.0f));
		powerup->SetSprite(powerup_sprite);
		powerup->SetScale(0.2f);
		mGameWorld->AddObject(powerup);
		mPowerUp = dynamic_pointer_cast<GameObject>(powerup);
	}
	else 
	if (rnd == 1) {
		Animation* anim_ptr = AnimationManager::GetInstance().GetAnimationByName("powerup_green");
		shared_ptr<Sprite> powerup_sprite = make_shared<Sprite>(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
		powerup_sprite->SetLoopAnimation(true);
		shared_ptr<Lazer> powerup = make_shared<Lazer>(mSpaceship, pos);
		powerup->SetBoundingShape(make_shared<BoundingSphere>(powerup->GetThisPtr(), 10.0f));
		powerup->SetSprite(powerup_sprite);
		powerup->SetScale(0.2f);
		mGameWorld->AddObject(powerup);
		mPowerUp = dynamic_pointer_cast<GameObject>(powerup);
	}
	else
	if (rnd == 2) {
		Animation* anim_ptr = AnimationManager::GetInstance().GetAnimationByName("powerup_orange");
		shared_ptr<Sprite> powerup_sprite = make_shared<Sprite>(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
		powerup_sprite->SetLoopAnimation(true);
		shared_ptr<Trishot> powerup = make_shared<Trishot>(mSpaceship, pos);
		powerup->SetBoundingShape(make_shared<BoundingSphere>(powerup->GetThisPtr(), 10.0f));
		powerup->SetSprite(powerup_sprite);
		powerup->SetScale(0.2f);
		mGameWorld->AddObject(powerup);
	}
	else if (rnd == 3) {
		Animation* anim_ptr = AnimationManager::GetInstance().GetAnimationByName("powerup_black");
		shared_ptr<Sprite> powerup_sprite = make_shared<Sprite>(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
		powerup_sprite->SetLoopAnimation(true);
		shared_ptr<AllAroundShot> powerup = make_shared<AllAroundShot>(mSpaceship, pos);
		powerup->SetBoundingShape(make_shared<BoundingSphere>(powerup->GetThisPtr(), 10.0f));
		powerup->SetSprite(powerup_sprite);
		powerup->SetScale(0.2f);
		mGameWorld->AddObject(powerup);
	}
	else if (rnd == 4) {
		Animation* anim_ptr = AnimationManager::GetInstance().GetAnimationByName("powerup_yellow");
		shared_ptr<Sprite> powerup_sprite = make_shared<Sprite>(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
		powerup_sprite->SetLoopAnimation(true);
		shared_ptr<OneUp> powerup = make_shared<OneUp>(make_shared<Player>(mPlayer), pos);
		powerup->SetBoundingShape(make_shared<BoundingSphere>(powerup->GetThisPtr(), 10.0f));
		powerup->SetSprite(powerup_sprite);
		powerup->SetScale(0.2f);
		mGameWorld->AddObject(powerup);
	}
}

void Asteroids::CreateAsteroids(const uint num_asteroids, const bool& isChildSpawn, const GLVector3f& pos)
{
	//changes size depending if its an original asteroid or one spawned due to another being destroid
	float scale;
	if (isChildSpawn) {
		scale = 0.08f;
	}
	else
	{
		scale = 0.2f;
	}
	mAsteroidCount += num_asteroids;
	for (uint i = 0; i < num_asteroids; i++)
	{
		int sprt_dcd = rand() % 3;
		string sprt_name = "asteroid1";
		//set a psydo random sprite to the asteroid 
		if (sprt_dcd == 0) {
			sprt_name == "asteroid1";
		}
		else if (sprt_dcd == 1) {
			sprt_name = "asteroid2";
		}
		else {
			sprt_name = "asteroid3";
		}
	
		//enter code above
		Animation* anim_ptr = AnimationManager::GetInstance().GetAnimationByName(sprt_name);
		shared_ptr<Sprite> asteroid_sprite
			= make_shared<Sprite>(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
		asteroid_sprite->SetLoopAnimation(true);
		//initialize astroid as empty
		shared_ptr<GameObject> asteroid;
		//check which kind of asteroid is spawning
		if (isChildSpawn) {
			//if it is a small asteroid, call constructor requiring isChildSpawn parameter
			asteroid = make_shared<Asteroid>(isChildSpawn, pos);
		}
		else {
			//if it is a large asteroid, call constructor without required parameters
			asteroid = make_shared<Asteroid>();
		}
		asteroid->SetBoundingShape(make_shared<BoundingSphere>(asteroid->GetThisPtr(), 10.0f));
		asteroid->SetSprite(asteroid_sprite);
		asteroid->SetScale(scale);
		mGameWorld->AddObject(asteroid);
		mAsteroids.push_back(asteroid);
	}
}

void Asteroids::CreateGUI()
{
	// Add a (transparent) border around the edge of the game display
	mGameDisplay->GetContainer()->SetBorder(GLVector2i(10, 10));
	// Create a new GUILabel and wrap it up in a shared_ptr
	mScoreLabel = make_shared<GUILabel>("Score: 0");
	// Set the vertical alignment of the label to GUI_VALIGN_TOP
	mScoreLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_TOP);
	// Add the GUILabel to the GUIComponent  
	shared_ptr<GUIComponent> score_component
		= static_pointer_cast<GUIComponent>(mScoreLabel);
	mGameDisplay->GetContainer()->AddComponent(score_component, GLVector2f(0.0f, 1.0f));

	// Create a new GUILabel and wrap it up in a shared_ptr
	mLivesLabel = make_shared<GUILabel>("Lives: 3");
	// Set the vertical alignment of the label to GUI_VALIGN_BOTTOM
	mLivesLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_BOTTOM);
	// Add the GUILabel to the GUIComponent  
	shared_ptr<GUIComponent> lives_component = static_pointer_cast<GUIComponent>(mLivesLabel);
	mGameDisplay->GetContainer()->AddComponent(lives_component, GLVector2f(0.0f, 0.0f));

	//temp to see astroid number
	//mAstroidNumLabel = make_shared<GUILabel>("Asteroids: " + mAsteroidCount);
	//mAstroidNumLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_BOTTOM);
	//shared_ptr<GUIComponent> astroid_num_component = static_pointer_cast<GUIComponent>(mAstroidNumLabel);
	//mGameDisplay->GetContainer()->AddComponent(astroid_num_component, GLVector2f(0.5f, 0.0f));
	
	// Create a new GUILabel and wrap it up in a shared_ptr
	mGameOverLabel = shared_ptr<GUILabel>(new GUILabel("GAME OVER"));
	// Set the horizontal alignment of the label to GUI_HALIGN_CENTER
	mGameOverLabel->SetHorizontalAlignment(GUIComponent::GUI_HALIGN_CENTER);
	// Set the vertical alignment of the label to GUI_VALIGN_MIDDLE
	mGameOverLabel->SetVerticalAlignment(GUIComponent::GUI_VALIGN_MIDDLE);
	// Set the visibility of the label to false (hidden)
	mGameOverLabel->SetVisible(false);
	// Add the GUILabel to the GUIContainer  
	shared_ptr<GUIComponent> game_over_component
		= static_pointer_cast<GUIComponent>(mGameOverLabel);
	mGameDisplay->GetContainer()->AddComponent(game_over_component, GLVector2f(0.5f, 0.5f));
}

void Asteroids::OnScoreChanged(int score)
{
	// Format the score message using an string-based stream
	std::ostringstream msg_stream;
	msg_stream << "Score: " << score;
	// Get the score message as a string
	std::string score_msg = msg_stream.str();
	mScoreLabel->SetText(score_msg);
}

void Asteroids::OnHealthChange(int live_lift) {
	// Format the lives left message using an string-based stream
	std::ostringstream msg_stream;
	msg_stream << "Lives: " << live_lift;
	// Get the lives left message as a string
	std::string lives_msg = msg_stream.str();
	mLivesLabel->SetText(lives_msg);
}

void Asteroids::OnPlayerKilled(int lives_left)
{
	shared_ptr<GameObject> explosion = CreateExplosion();
	explosion->SetPosition(mSpaceship->GetPosition());
	explosion->SetRotation(mSpaceship->GetRotation());
	mGameWorld->AddObject(explosion);

	OnHealthChange(lives_left);

	if (lives_left > 0) 
	{ 
		SetTimer(1000, CREATE_NEW_PLAYER); 
	}
	else
	{
		SetTimer(500, SHOW_GAME_OVER);
	}
}

shared_ptr<GameObject> Asteroids::CreateExplosion()
{
	Animation *anim_ptr = AnimationManager::GetInstance().GetAnimationByName("explosion");
	shared_ptr<Sprite> explosion_sprite =
		make_shared<Sprite>(anim_ptr->GetWidth(), anim_ptr->GetHeight(), anim_ptr);
	explosion_sprite->SetLoopAnimation(false);
	shared_ptr<GameObject> explosion = make_shared<Explosion>();
	explosion->SetSprite(explosion_sprite);
	explosion->Reset();
	return explosion;
}