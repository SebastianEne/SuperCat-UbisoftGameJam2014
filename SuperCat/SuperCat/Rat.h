#pragma once

#include "irrlicht\irrlicht.h"
#include "irrKlang\irrKlang.h"
#include "irrlicht\driverChoice.h"
#include "Coin.h"
#include "Cat.h"
#include <iostream>
using namespace irr;
using namespace irrklang;

class Rat {
public:
	Rat(void);
	~Rat(void);
	Rat(scene::ISceneManager*, gui::IGUIStaticText *, ISoundEngine*, gui::IGUIEnvironment*, video::IVideoDriver*);
	void move(Cat *);
	void move_around_coin();
private:
	void faceTarget(irr::core::vector3df);
	double Distance(double, double, double, double);
private:
	scene::ISceneManager* smgr;
	gui::IGUIStaticText *text;
	ISoundEngine* engine;
	video::IVideoDriver* driver;
	gui::IGUIEnvironment* env;
public:
	scene::IAnimatedMeshSceneNode* node;
	Coin *coin;
};

