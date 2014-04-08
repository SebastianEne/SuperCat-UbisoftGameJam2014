#include "World.h"


World::World(void) {}
World::~World(void) {}

World::World(scene::ISceneManager *smgr, video::IVideoDriver* driver) {
	
	this->smgr = smgr;
	this->driver = driver;

	// add terrain scene node
	this->terrain = smgr->addTerrainSceneNode(
		"media/light.bmp",
		0,									// parent node
		-1,									// node id
		core::vector3df(0.f, 0.f, 0.f),		// position
		core::vector3df(0.f, 0.f, 0.f),		// rotation
		core::vector3df(40.f, 4.4f, 40.f),	// scale
		video::SColor ( 255, 255, 255, 255 ),// vertexColor
		5,									// maxLOD
		scene::ETPS_17,						// patchSize
		4									// smoothFactor
		);

	this->terrain->setMaterialFlag(video::EMF_LIGHTING, false);
	this->terrain->setMaterialTexture(0, this->driver->getTexture("media/terrain-texture.jpg"));
	this->terrain->setMaterialTexture(1, this->driver->getTexture("media/detailmap3.jpg"));	
	this->terrain->setMaterialType(video::EMT_DETAIL_MAP);
	this->terrain->scaleTexture(1.0f, 20.0f);

	// create skybox and skydome
	this->driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);
	scene::ISceneNode* skybox = this->smgr->addSkyBoxSceneNode(
		this->driver->getTexture("media/irrlicht2_up.jpg"),
		this->driver->getTexture("media/irrlicht2_dn.jpg"),
		this->driver->getTexture("media/irrlicht2_lf.jpg"),
		this->driver->getTexture("media/irrlicht2_rt.jpg"),
		this->driver->getTexture("media/irrlicht2_ft.jpg"),
		this->driver->getTexture("media/irrlicht2_bk.jpg"));
	scene::ISceneNode* skydome = this->smgr->addSkyDomeSceneNode(this->driver->getTexture("media/skydome.jpg"),16,8,0.95f,2.0f);
	this->driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);

	// Adaug model peste(plan texturat cu canal de alpha)
	scene::IAnimatedMesh* peste_mesh = smgr->getMesh("media/textures_planes/pine_trees.obj");
	scene::IAnimatedMeshSceneNode* peste_node = this->smgr->addAnimatedMeshSceneNode(peste_mesh);	
	if(peste_mesh == NULL) {
		printf("Nu putem incarca mesh-ul de player\n");
		exit(-1);
	}

	this->smgr->addMeshSceneNode(peste_mesh);
	peste_node->setRotation(core::vector3df(90, 0, 0));
	peste_node->setScale(core::vector3df(100, 100, 100));
	peste_node->setPosition(core::vector3df(2100*2, -20, 2800*2));
	peste_node->setMaterialFlag(video::EMF_LIGHTING, false);
	peste_node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);

}
