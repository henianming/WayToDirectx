#ifndef WNDPROC_EVENT_MGR_H
#define WNDPROC_EVENT_MGR_H

#include <Windows.h>
#include <vector>
#include <list>

enum HEventType {
	EventType_Min = 0,
	EventType_KeyDown,
	EventType_KeyUp,
	EventType_LBUTTONDOWN,
	EventType_RBUTTONDOWN,
	EventType_MOUSEMOVE,
	EventType_LBUTTONUP,
	EventType_RBUTTONUP,
	EventType_Max,
};

class HIWndProcEventReceiver {
public:
	virtual BOOL OnMessage(HEventType eventType, WPARAM wParam, LPARAM lParam) = 0;
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

	void Subscribe(HIWndProcEventReceiver *receiver, HEventType eventType);
	void Unsubscribe(HIWndProcEventReceiver *receiver, HEventType eventType);
	BOOL FireEvent(HEventType eventType, WPARAM wParam, LPARAM lParam);
};

#endif