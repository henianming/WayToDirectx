#ifndef WNDPROC_EVENT_MGR_H
#define WNDPROC_EVENT_MGR_H

#include <Windows.h>
#include <vector>
#include <list>

enum EventType {
	EventType_Min = 0,
	EventType_Max,
};

class WndProcEventReceiver {
public:
	virtual void OnMessage(EventType eventType, void const *param) = 0;
};

class WndProcEventMgr {
public:
	typedef std::list<WndProcEventReceiver*> M_RL;
	typedef std::vector<M_RL*> M_ETV;

private:
	M_ETV m_etv;

public:
	BOOL Create();
	BOOL Release();

	void Subscribe(WndProcEventReceiver *receiver, EventType eventType);
	void Unsubscribe(WndProcEventReceiver *receiver, EventType eventType);
	BOOL FireEvent(EventType eventType, void const *param);
};

#endif