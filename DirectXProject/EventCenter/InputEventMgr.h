#pragma once

#include <Windows.h>
#include <list>
#include <vector>

enum HInputEventType {
	HInputEventType_Min = 0,
	HInputEventType_W,
	HInputEventType_A,
	HInputEventType_S,
	HInputEventType_D,
	HInputEventType_SPACE,
	HInputEventType_SHIFT,
	HInputEventType_Max,
};

//--------分界线-----------------------------------------------------------------
class HIInputEventReceiver {
public:
	virtual BOOL OnMessage(HInputEventType eventType, DOUBLE durationTime, DOUBLE firstActiveTimeStamp, BOOL isContinue) = 0;
};

//--------分界线-----------------------------------------------------------------
class HInputEventMgr {
private:
	typedef std::list<HIInputEventReceiver*> M_RL;
	typedef std::vector<M_RL*> M_ETV;

private:
	M_ETV m_etv;

public:
	BOOL Create();
	BOOL Release();

	VOID Subscribe(HIInputEventReceiver *receiver, HInputEventType eventType);
	VOID Unsubscribe(HIInputEventReceiver *receiver, HInputEventType eventType);
	BOOL FireEvent(HInputEventType eventType, DOUBLE durationTime, DOUBLE firstActiveTimeStamp, BOOL isContinue);
};