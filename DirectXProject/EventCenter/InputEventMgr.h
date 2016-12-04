#if 0
#pragma once

#include <Windows.h>
#include <list>
#include <vector>

enum HInputEventType {
	HInputEventType_Min,
	HInputEventType_W,
	HInputEventType_A,
	HInputEventType_S,
	HInputEventType_D,
	HInputEventType_Max,
};

class HIInputEventReceiver {
public:
	virtual BOOL OnMessage(HInputEventType eventType, double durationTime, BOOL isContinue) = 0;
};

class HInputEventMgr {
private:
	typedef std::list<HIInputEventReceiver*> M_RL;
	typedef std::vector<M_RL*> M_ETV;

private:
	M_ETV m_etv;

public:
	BOOL Create();
	BOOL Release();

	void Subscribe(HIInputEventReceiver *receiver, HInputEventType eventType);
	void Unsubscribe(HIInputEventReceiver *receiver, HInputEventType eventType);
	BOOL FireEvent(HInputEventType eventType, double durationTime, BOOL isContinue);
};
#endif