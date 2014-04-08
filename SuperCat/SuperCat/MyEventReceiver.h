#pragma once

#include "irrlicht\irrlicht.h"
using namespace irr;

class MyEventReceiver : public IEventReceiver {

public:
	MyEventReceiver(void);
	~MyEventReceiver(void);
	virtual bool OnEvent(const SEvent&);
	virtual bool IsKeyDown(EKEY_CODE);
private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];

};

