#include "irrlicht\irrlicht.h"
#include "irrKlang\irrKlang.h"
#include "irrlicht\driverChoice.h"
#include "irrlicht\ISceneCollisionManager.h"
#include <math.h>
#include <vector>

#include "Rat.h"
#include "Cat.h"
#include "MyEventReceiver.h"
#include "World.h"

using namespace irr;
using namespace irrklang;

int scor = 0;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrKlang.lib")
#endif

int main() {

	irr::SIrrlichtCreationParameters params;
	params.DriverType=video::EDT_OPENGL;
	params.Fullscreen = true;
	params.WindowSize=core::dimension2d<u32>(1264, 768);
	IrrlichtDevice* device = createDeviceEx(params);
	if (device == 0)	
		return 1; 

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	gui::IGUIEnvironment* env = device->getGUIEnvironment();
	driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

	ISoundEngine* engine = createIrrKlangDevice();
	if (!engine) {
		printf("Could not startup engine\n");
		return 0; // error starting up the engine
	}
	engine->play2D("media/sounds/background.wav", false);
	// harta
	env->addImage(driver->getTexture("media/map.png"), core::position2d<int>(10,10));
	gui::IGUIImage *little_cat = env->addImage(driver->getTexture("media/littlecat.png"), core::position2d<int>(60,60));

	// disable mouse cursor
	device->getCursorControl()->setVisible(false);

	World *world = new World(smgr, driver);

	// create triangle selector for the terrain	
	scene::ITriangleSelector* selector
		= smgr->createTerrainTriangleSelector(world->terrain, 0);
	world->terrain->setTriangleSelector(selector);

	// afisare scor
	env->getSkin()->setFont(env->getFont("media/fontlucida.png"));
	gui::IGUIStaticText *text = env->addStaticText(
		L"Coins: 0",
		core::rect<s32>(10,400,150,420), true, true, 0, -1, true);
	 
	// animmalele din scena

	Cat *cat = new Cat(smgr);

	std::vector<Rat *> sobolani;
	for (int i = 0; i < 5; i++) {
		Rat *rat = new Rat(smgr, text, engine, env, driver);
		sobolani.push_back(rat);
	}

	std::vector<gui::IGUIImage *> vieti;
	for (int i = 0; i < cat->vieti; i++) {
		gui::IGUIImage *viata = env->addImage(driver->getTexture("media/heart.png"), core::position2d<int>(500 + i * 35,30));
		vieti.push_back(viata);
	}

	// create collision response animator and attach it to the camera
	scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
		selector, cat->node, core::vector3df(1,1,1),
		core::vector3df(0,-1.0f,0),
		core::vector3df(0,0,0));
	selector->drop();
	cat->node->addAnimator(anim);
	anim->drop();

	// create event receiver
	MyEventReceiver receiver = MyEventReceiver();
	device->setEventReceiver(&receiver);
	u32 then = device->getTimer()->getTime();

	bool up = false;
	int counter = 0;

	int coins = 0;
	bool player = false;

	while(device->run())
	if (device->isWindowActive()) {

		if ((coins != cat->score) && (sobolani.size() < 10)) {
		
			coins = cat->score;
			Rat *rat = new Rat(smgr, text, engine, env, driver);
			sobolani.push_back(rat);

		}

		// Work out a frame delta time.
		const u32 now = device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32)(now - then) / 1000.f; 
		then = now;

		driver->beginScene(true, true, 0 );

		/* Aici interpretam cum reactioneaza obiectul la apasarea de taste *
			! de mutat in functie separat 
		*/

		if (cat->vieti == 0) {

			vieti[0]->setVisible(false);
			env->addImage(driver->getTexture("media/gameover.png"), core::position2d<int>(280,200));
			smgr->drawAll();
			env->drawAll();
			driver->endScene();
			continue;
		}

		if(receiver.IsKeyDown(KEY_KEY_W)) {
			cat->move(KEY_KEY_W, frameDeltaTime);
		} else if(receiver.IsKeyDown(KEY_KEY_S)) {
			cat->move(KEY_KEY_S, frameDeltaTime);
		}

		if(receiver.IsKeyDown(KEY_KEY_A))
			cat->move(KEY_KEY_A, frameDeltaTime);
		if(receiver.IsKeyDown(KEY_KEY_D))
			cat->move(KEY_KEY_D, frameDeltaTime);
		if(receiver.IsKeyDown(KEY_SPACE) && !up && (counter == 0)) {
			cat->move(KEY_SPACE, frameDeltaTime);
			cat->v = 300;
			up = true;
			counter++;
			cat->node->setFrameLoop(55, 78);
			engine->play2D("media/sounds/jump.wav", false);
		}
		if(!receiver.IsKeyDown(KEY_SPACE) && up && (counter == 0)) {
			up = false;
			cat->node->setFrameLoop(0, 55);
		}                                                                                                                   

		int max = 120;
		if ((counter > 0) && (counter < max)) {
			cat->move(KEY_SPACE, frameDeltaTime);
			counter++;
			if (counter == max)
				counter = 0;
		}

		cat->move2();

		for (int i = 0; i < sobolani.size(); i++) {
			Rat * rat = sobolani[i];
			rat->move(cat);
			rat->coin->move();
			rat->coin->coliziune(cat);
		}

		/*
		rat->move(cat);
		rat->coin->move();
		rat->coin->coliziune(cat);

		rat2->move(cat);
		rat2->coin->move();
		rat2->coin->coliziune(cat);

		rat3->move(cat);
		rat3->coin->move();
		rat3->coin->coliziune(cat);

		rat4->move(cat);
		rat4->coin->move();
		rat4->coin->coliziune(cat);
		*/
		// vieti si misica moarta
		if ((cat->dead) && (cat->vieti > 0)) {
			gui::IGUIImage *viata = vieti[cat->vieti];
			//vieti.pop_back();
			viata->setVisible(false);
			
		}

		if (cat->vieti == 0)
			vieti[0]->setVisible(false);

		smgr->drawAll();
		env->drawAll();

		driver->endScene();

	}

	while (1);

	device->drop();
	return 0;

}
