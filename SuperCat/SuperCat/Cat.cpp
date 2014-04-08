#include "Cat.h"

using namespace core;

Cat::Cat(void) {}
Cat::~Cat(void) {}

Cat::Cat(scene::ISceneManager *smgr) {

	this->smgr = smgr;

	//  Adaug modelul la lista de desenare 
	scene::IAnimatedMesh* player_mesh = this->smgr->getMesh("models/cat/cat_rigged.b3d");
	this->node = this->smgr->addAnimatedMeshSceneNode(player_mesh);	
	if(player_mesh == NULL) {
		printf("Nu putem incarca mesh-ul de player\n");
		exit(-1);
	}
	this->node->setScale(core::vector3df(40,40,40));
	this->node->setRotation(core::vector3df(0.0f, 180, 0.0f));
	this->node->setPosition(core::vector3df(2600*2, 20*2, 2000*2));
	this->node->setMaterialFlag(video::EMF_LIGHTING, false);
	this->node->setFrameLoop(0, 55);
	this->node->updateAbsolutePosition();
	this->node->setAnimationSpeed(30);

	// Adaug o camera la scena
	this->camera = this->smgr->addCameraSceneNode();
	this->camera->setPosition(core::vector3df(0, 10, 15));
	this->camera->setFarValue(42000.0f);
	this->camera->setTarget(this->node->getPosition());


//	this->camera->setParent(this->node);
	this->score = 0;
	this->vieti = 3;
	this->dead = false;

	srand (time(NULL));
	this->v = 200;

	vector3df des_pos = this->node->getAbsolutePosition();
	des_pos += get_axis(0) * 0 + get_axis(1) * 10 + get_axis(2) * 15;
	des_pos.Y = 300;
	camera->setPosition(des_pos);

}

void Cat::move(EKEY_CODE key, float frameDeltaTime) {

	if (this->dead) {
		int iSecret = rand() % 10 + 1;
		this->node->setPosition(core::vector3df(2600*2, 30*2, 200*2*iSecret));
		this->node->setRotation(core::vector3df(0.0f, 180, 0.0f));
		this->camera->setTarget(this->node->getPosition());
		vector3df des_pos = this->node->getAbsolutePosition();
		des_pos += get_axis(0) * 0 + get_axis(1) * 10 + get_axis(2) * 15;
		des_pos.Y = 300;
		camera->setPosition(des_pos);
		this->dead = false;
	}

	core::vector3df vectorPosition = this->node->getPosition();
	this->angle = this->node->getRotation().Y;
	core::vector3df camPosition = this->camera->getPosition();

	float angrad = (angle - 90.0f) / 180.0f * PI;

	if (key == KEY_KEY_W) {
		vectorPosition.Z += sin(angrad) * MOVE_SPEED * frameDeltaTime;
		vectorPosition.X -= cos(angrad) * MOVE_SPEED * frameDeltaTime;
		this->camera->setTarget(vectorPosition);
	} else if (key == KEY_KEY_S) {
		vectorPosition.Z -= sin(angrad) * MOVE_SPEED * frameDeltaTime;
		vectorPosition.X += cos(angrad) * MOVE_SPEED * frameDeltaTime;
		this->camera->setTarget(vectorPosition);
	}

	if (key == KEY_KEY_A) {
		angle -= (180) * frameDeltaTime;
	}

	if (key == KEY_KEY_D) {
		angle += (180) * frameDeltaTime;
	}

	if (key == KEY_SPACE) {

		float a = -300;
		//vectorPosition.Y += 200 * frameDeltaTime;
		v = v + (a * frameDeltaTime);
		vectorPosition.Y += v * frameDeltaTime;
	}

	this->node->setPosition(vectorPosition);
	core::vector3df newROT = this->node->getRotation();
	newROT.Y = angle;
	this->node->setRotation(newROT);
	/*
	vector3df des_pos = this->node->getAbsolutePosition();
	des_pos += get_axis(0) * 0 + get_axis(1) * 10 + get_axis(2) * 15;
	vector3df last_pos = camera->getPosition();
	static float blend = 0.05;
	vector3df cam_pos = des_pos * blend + last_pos * (1 - blend);
	cam_pos.Y = 300;
	camera->setPosition(cam_pos);
	*/
}

vector3df Cat::get_axis(int i) {

	const matrix4 &m = this->node->getAbsoluteTransformation();
	return vector3df(m[0 + i * 4], m[1 + i * 4], m[2 + i * 4]);

}

void Cat::move2() {

	vector3df des_pos = this->node->getAbsolutePosition();
	des_pos += get_axis(0) * 0 + get_axis(1) * 10 + get_axis(2) * 15;
	vector3df last_pos = camera->getPosition();
	static float blend = 0.05;
	vector3df cam_pos = des_pos * blend + last_pos * (1 - blend);
	cam_pos.Y = 300;
	camera->setPosition(cam_pos);

}

