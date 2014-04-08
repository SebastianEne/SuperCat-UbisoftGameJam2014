#include "Coin.h"


Coin::Coin(void) {}
Coin::~Coin(void) {}

double Coin::Distance(double dX0, double dY0, double dX1, double dY1) {
	return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}

Coin::Coin(scene::ISceneManager *smgr, gui::IGUIStaticText *text, ISoundEngine* engine, gui::IGUIEnvironment* env, video::IVideoDriver* driver) {

	this->smgr = smgr;
	this->text = text;
	this->engine = engine;
	this->env = env;
	this->driver = driver;

	this->contor = 120;

	scene::IAnimatedMesh* building_mesh = this->smgr->getMesh("models/cheese/cheese.obj");
	this->node = this->smgr->addAnimatedMeshSceneNode(building_mesh);	
	if(building_mesh == NULL) {
		printf("Nu putem incarca mesh-ul de player\n");
		exit(-1);
	}

	this->node->setScale(core::vector3df(80,80,80));
	this->node->setPosition(core::vector3df((1 + rand() % 10) * 550, 30*2, (1 + rand() % 15) * 500));
	this->node->setMaterialFlag(video::EMF_LIGHTING, false);
	this->node->setRotation(core::vector3df(0, 0, 90));

	this->dead = false;

}

void Coin::coliziune(Cat *cat) {

	if (this->dead) {

		this->contor--;

		if (this->contor == 0) 
			this->imag->setVisible(false);

		return;
	}

	double d = Distance(cat->node->getPosition().X, cat->node->getPosition().Z, this->node->getPosition().X, this->node->getPosition().Z);

	//std::cout << dif.X << " " << dif.Y << " " << dif.Z << std::endl;
	if (d < 80) {

		this->imag = env->addImage(driver->getTexture("media/welldone.png"), core::position2d<int>(120,120));

		this->engine->play2D("media/sounds/coin.wav", false);

		this->dead = true;
		this->smgr->addToDeletionQueue(this->node);
		std::string scor = "Coins: ";
		cat->score++;
		scor += std::to_string(cat->score);
		std::wstring widestr = std::wstring(scor.begin(), scor.end());
		const wchar_t* widecstr = widestr.c_str();
		text->setText(widecstr);
	}

}

void Coin::move() {

	if (this->dead)
		return;

	this->node->setRotation(this->node->getRotation() + core::vector3df(1, 0, 0));

}
