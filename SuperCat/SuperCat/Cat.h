#pragma once

#include "irrlicht\irrlicht.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>  
#include <time.h>  
using namespace irr;

#define PI 3.147
#define MOVE_SPEED 550

class Cat {
public:
	Cat(void);
	~Cat(void);
	Cat(scene::ISceneManager*);
	void move(EKEY_CODE, float);
	core::vector3df get_axis(int); 
	void move2();
private:
	scene::ISceneManager* smgr;
	float angle;
	core::vector3df jump_velocity;
	bool accelerate;
	int counter;
public:
	scene::IAnimatedMeshSceneNode* node;
	scene::ICameraSceneNode* camera;
	int score;
	int vieti;
	bool dead;
	float v;
};

