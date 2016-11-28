#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include "Input.h"

class HKeyboardInput : public HIInputDevice {
public:
	BOOL Create();
	BOOL Release();

public:
	virtual BOOL OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam);
};

#endif //KEYBOARD_INPUT_H