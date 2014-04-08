#pragma once

#include "irrlicht\irrlicht.h"
using namespace irr;

class World {
public:
	World(void);
	~World(void);
	World(scene::ISceneManager*, video::IVideoDriver*);
private:
	scene::ISceneManager* smgr;
	video::IVideoDriver* driver;
public:
	scene::ITerrainSceneNode* terrain;
};

