#include "Rat.h"

Rat::Rat(void) {}
Rat::~Rat(void) {}

double Rat::Distance(double dX0, double dY0, double dX1, double dY1) {
	return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}

void Rat::faceTarget(irr::core::vector3df targetPos) {

	core::vector3df myRotation = this->node->getRotation();
	core::vector3df nodePos = targetPos - this->node->getPosition();
	myRotation.Y = atan(nodePos.Z/nodePos.X) * (180.0f / 3.14f); // irr::core::PI
	
	if((targetPos.X - this->node->getPosition().X) > 0) {
		myRotation.Y = 90 - myRotation.Y;
	} else if((targetPos.X - this->node->getPosition().X) < 0) {
		myRotation.Y = -90 - myRotation.Y;
	}

	myRotation.Y -= 90;
	this->node->setRotation(myRotation);

}

Rat::Rat(scene::ISceneManager *smgr, gui::IGUIStaticText *text, ISoundEngine* engine, gui::IGUIEnvironment* env, video::IVideoDriver* driver) {

	this->smgr = smgr;
	this->text = text;
	this->engine = engine;
	this->env = env;
	this->driver = driver;

	scene::IAnimatedMesh* building_mesh = this->smgr->getMesh("media/rat/rat.b3d");
	this->node = this->smgr->addAnimatedMeshSceneNode(building_mesh);	
	if(building_mesh == NULL) {
		printf("Nu putem incarca mesh-ul de player\n");
		exit(-1);
	}

	this->node->setScale(core::vector3df(50,50,50));
	this->node->setPosition(core::vector3df(2000*2, 50*2, 2600*2));
	this->node->setMaterialFlag(video::EMF_LIGHTING, false);
	this->node->setAnimationSpeed(30);

	this->coin = new Coin(this->smgr, this->text, this->engine, this->env, this->driver);

	/* Aici setez obiectul sa se miste in jurul monezii */
	scene::ISceneNodeAnimator* anim = smgr->createFlyCircleAnimator(this->coin->node->getPosition(), 360, 0.001f);	
	node->addAnimator(anim);
	anim->drop();

}

void Rat::move(Cat *cat) {

	double d = Distance(cat->node->getPosition().X, cat->node->getPosition().Z, this->node->getPosition().X, this->node->getPosition().Z);

	if (d < 90) {

		if (cat->vieti == 0)
			return;

		cat->vieti--;

		std::string scor = "Coins: ";
		scor += std::to_string(cat->score);
		std::wstring widestr = std::wstring(scor.begin(), scor.end());
		const wchar_t* widecstr = widestr.c_str();
		this->text->setText(widecstr);

		cat->dead = true;

		int iSecret = rand() % 10 + 1;
		cat->node->setPosition(core::vector3df(2600*2.0f, 30*2.0f, 200*2.0f*iSecret));
		cat->node->setRotation(core::vector3df(0.0f, 180, 0.0f));
		cat->camera->setTarget(this->node->getPosition());
		core::vector3df des_pos = cat->node->getAbsolutePosition();
		des_pos += cat->get_axis(0) * 0 + cat->get_axis(1) * 10 + cat->get_axis(2) * 15;
		des_pos.Y = 300;
		cat->camera->setPosition(des_pos);

	} else if (d < 650) {
		node->removeAnimators();
		core::vector3df dif = cat->node->getPosition() - this->node->getPosition();
		dif = dif / 100;
		this->node->setPosition(this->node->getPosition() + dif);
		faceTarget(cat->node->getPosition());
	} else if (!this->coin->dead) {
		core::vector3df dif = (this->coin->node->getPosition() - this->node->getPosition());
		dif = dif / 200;
		this->node->setPosition(this->node->getPosition() + dif);
		faceTarget(this->coin->node->getPosition());
	}

	if (this->coin->dead) {
		node->removeAnimators();
		core::vector3df dif = cat->node->getPosition() - this->node->getPosition();
		dif = dif / 100;
		this->node->setPosition(this->node->getPosition() + dif);
		faceTarget(cat->node->getPosition());
	}

}

void Rat::move_around_coin() {}