#ifndef WNDPROC_EVENT_MGR_H
#define WNDPROC_EVENT_MGR_H

#include <Windows.h>
#include <vector>
#include <list>

enum EventType {
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

class WndProcEventReceiver {
public:
	virtual BOOL OnMessage(EventType eventType, WPARAM wParam, LPARAM lParam) = 0;
};

class WndProcEventMgr {
private:
	typedef std::list<WndProcEventReceiver*> M_RL;
	typedef std::vector<M_RL*> M_ETV;

private:
	M_ETV m_etv;

public:
	BOOL Create();
	BOOL Release();

	void Subscribe(WndProcEventReceiver *receiver, EventType eventType);
	void Unsubscribe(WndProcEventReceiver *receiver, EventType eventType);
	BOOL FireEvent(EventType eventType, WPARAM wParam, LPARAM lParam);
};

#endif