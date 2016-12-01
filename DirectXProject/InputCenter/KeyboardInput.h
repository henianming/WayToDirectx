#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include "Input.h"
#include <list>
#include <Windows.h>

struct HKeyboard_Data {
	WPARAM m_key;
	BOOL m_isContinue;
	double m_lastActiveTimeStamp;
};

class HKeyboardInput : public HIInputDevice {
private:
	typedef std::list<HKeyboard_Data*> M_KDL;

private:
	M_KDL m_keyboardDataList;

private:
	void SubscribeEvent();
	void UnsubscribeEnent();
	BOOL IsKeyActive(WPARAM m_key);

public:
	virtual BOOL Create();
	virtual BOOL Release();
	virtual BOOL Update();
	virtual BOOL OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam);
};

#endif //KEYBOARD_INPUT_H