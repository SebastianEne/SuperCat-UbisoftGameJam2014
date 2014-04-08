#include "MyEventReceiver.h"

MyEventReceiver::MyEventReceiver(void) {
	for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i) {
		KeyIsDown[i]= false;
	}
}
MyEventReceiver::~MyEventReceiver(void) {}

bool MyEventReceiver::IsKeyDown(EKEY_CODE keyCode) {
	return KeyIsDown[keyCode];
}

bool MyEventReceiver::OnEvent(const SEvent& event) {

	// Remember whether each key is down or up
	if ((event.EventType == irr::EET_KEY_INPUT_EVENT))
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	return false;

}
