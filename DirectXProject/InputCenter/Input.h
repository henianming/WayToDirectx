#ifndef INPUT_H
#define INPUT_H

#include <Windows.h>

#include "EventCenter/WndProcEventMgr.h"
#include "EventCenter/InputEventMgr.h"
#include "KeyboardInput.h"

class HIInputDevice : public HIWndProcEventReceiver {
public:
	virtual BOOL Create() = 0;
	virtual BOOL Release() = 0;
};                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 

class HInputMgr : public HIInputEventReceiver {
private:
	HKeyboardInput m_keyboard;

public:
	BOOL Create();
	BOOL Release();

public:
	virtual BOOL OnMessage(HInputEventType eventType, double durationTime, BOOL isContinue);
};

#endif //INPUT_H