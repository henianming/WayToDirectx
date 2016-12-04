#pragma once

#include <Windows.h>
#include <vector>
#include <list>

enum HWndProcEventType {
	WndProcEventType_Min = 0,
	WndProcEventType_KeyDown,
	WndProcEventType_KeyUp,
	WndProcEventType_LBUTTONDOWN,
	WndProcEventType_RBUTTONDOWN,
	WndProcEventType_MOUSEMOVE,
	WndProcEventType_LBUTTONUP,
	WndProcEventType_RBUTTONUP,
	WndProcEventType_Max,
};

class HIWndProcEventReceiver {
public:
	virtual BOOL OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam) = 0;
};

class HWndProcEventMgr {
private:
	typedef std::list<HIWndProcEventReceiver*> M_RL;
	typedef std::vector<M_RL*> M_ETV;

private:
	M_ETV m_etv;

public:
	BOOL Create();
	BOOL Release();

	void Subscribe(HIWndProcEventReceiver *receiver, HWndProcEventType eventType);
	void Unsubscribe(HIWndProcEventReceiver *receiver, HWndProcEventType eventType);
	BOOL FireEvent(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam);
};