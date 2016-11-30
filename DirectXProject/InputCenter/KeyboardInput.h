#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include "Input.h"

class HKeyboardInput : public HIInputDevice {
private:
	void SubscribeEvent();
	void UnsubscribeEnent();

public:
	virtual BOOL Create();
	virtual BOOL Release();
	virtual BOOL Update();
	virtual BOOL OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam);
};

#endif //KEYBOARD_INPUT_H