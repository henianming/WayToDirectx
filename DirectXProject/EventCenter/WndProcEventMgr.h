#pragma once

#include <Windows.h>
#include <vector>
#include <list>

enum HWndProcEventType {
	HWndProcEventType_MIN = 0,
	HWndProcEventType_KEYDOWN,
	HWndProcEventType_KEYUP,
	HWndProcEventType_LBUTTONDOWN,
	HWndProcEventType_RBUTTONDOWN,
	HWndProcEventType_MOUSEMOVE,
	HWndProcEventType_LBUTTONUP,
	HWndProcEventType_RBUTTONUP,
	HWndProcEventType_MOVE,
	HWndProcEventType_MOVING,
	HWndProcEventType_SIZE,
	HWndProcEventType_SIZING,
	HWndProcEventType_MAX,
};

//--------分界线-----------------------------------------------------------------
class HIWndProcEventReceiver {
public:
	virtual BOOL OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam) = 0;
};

//--------分界线-----------------------------------------------------------------
class HWndProcEventMgr {
private:
	typedef std::list<HIWndProcEventReceiver*> M_RL;
	typedef std::vector<M_RL*> M_ETV;

private:
	M_ETV m_etv;

public:
	BOOL Create();
	BOOL Release();

	VOID Subscribe(HIWndProcEventReceiver *receiver, HWndProcEventType eventType);
	VOID Unsubscribe(HIWndProcEventReceiver *receiver, HWndProcEventType eventType);
	BOOL FireEvent(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam);
};