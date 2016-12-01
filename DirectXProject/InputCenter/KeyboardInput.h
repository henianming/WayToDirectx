#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include "Input.h"
#include <list>
#include <map>
#include <Windows.h>

struct HKeyboard_Data {
	HInputEventType m_key;
	double m_lastActiveTimeStamp;
};

class HKeyboardInput : public HIInputDevice {
private:
	typedef std::map<WPARAM, HInputEventType> M_KIEM;
	typedef std::pair<WPARAM, HInputEventType> M_KIEP;
	typedef std::list<HKeyboard_Data*> M_KDL;

private:
	M_KIEM m_keyEventMap;
	M_KDL m_keyboardDataList;

private:
	void CreateKeyboardMap();
	void ReleaseKeyboardMap();
	void SubscribeEvent();
	void UnsubscribeEnent();
	M_KDL::iterator IsKeyActive(HInputEventType key);
	HInputEventType VKToRK(WPARAM key);

public:
	virtual BOOL Create();
	virtual BOOL Release();
	virtual BOOL Update();
	virtual BOOL OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam);
};

#endif //KEYBOARD_INPUT_H