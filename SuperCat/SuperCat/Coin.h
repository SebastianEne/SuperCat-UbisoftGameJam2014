#pragma once
#include "irrlicht\irrlicht.h"
#include "irrKlang\irrKlang.h"
#include "irrlicht\driverChoice.h"
#include <iostream>
#include <string>
#include "Cat.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
using namespace irr;
using namespace irrklang;

class Coin {

public:
	Coin(void);
	~Coin(void);
	Coin(scene::ISceneManager*, gui::IGUIStaticText *, ISoundEngine*, gui::IGUIEnvironment*, video::IVideoDriver*);
	void move();
	void coliziune(Cat*);
private:
	double Distance(double, double, double, double);
private:
	scene::ISceneManager* smgr;
	gui::IGUIStaticText *text;
	ISoundEngine* engine;
	video::IVideoDriver* driver;
	gui::IGUIEnvironment* env;
	gui::IGUIImage *imag;
	int contor;
public:
	scene::IAnimatedMeshSceneNode* node;
	bool dead;
};

