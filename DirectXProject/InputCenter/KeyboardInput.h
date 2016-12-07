#pragma once

#include "Input.h"
#include <list>
#include <map>
#include "EventCenter/WndProcEventMgr.h"
#include "EventCenter/InputEventMgr.h"
#include "InputCenter/Input.h"

struct HKeyboard_Data {
	HInputEventType m_key;
	DOUBLE m_firstActiveTimeStamp;
	DOUBLE m_lastActiveTimeStamp;
};

//--------·Ö½çÏß-----------------------------------------------------------------
class HKeyboardInput : public HIInputDevice, public HIWndProcEventReceiver {
private:
	typedef std::map<WPARAM, HInputEventType> M_KIEM;
	typedef std::pair<WPARAM, HInputEventType> M_KIEP;
	typedef std::list<HKeyboard_Data*> M_KDL;

private:
	M_KIEM m_keyEventMap;
	M_KDL m_keyboardDataList;

private:
	VOID CreateKeyboardMap();
	VOID ReleaseKeyboardMap();
	VOID SubscribeEvent();
	VOID UnsubscribeEnent();
	M_KDL::iterator IsKeyActive(HInputEventType key);
	HInputEventType VKToRK(WPARAM key);

public:
	virtual BOOL Create();
	virtual BOOL Release();
	virtual BOOL Update();
	virtual BOOL OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam);
};