#pragma once

#include <Windows.h>
#include <map>

#include "TimeCenter/Time.h"

//--------分界线-----------------------------------------------------------------
struct HTimerData {
public:
	HTime const *m_time;
	DOUBLE m_intervalTime;
	DOUBLE m_lastActiveTime;

public:
	HTimerData(HTime const *time, DOUBLE intervalTime, DOUBLE lastActiveTime);
};

//--------分界线-----------------------------------------------------------------
class HITimerMgrReceiver {
public:
	virtual VOID OnTimer(INT id) = 0;
};

//--------分界线-----------------------------------------------------------------
class HTimerMgr {
private:
	typedef std::map<INT, HTimerData> M_ID_INTERVAL;
	typedef std::map<HITimerMgrReceiver*, M_ID_INTERVAL*> M_RECEIVER_ID;

private:
	M_RECEIVER_ID m_receiver_id;
	HTime m_time;

public:
	BOOL Create();
	BOOL Release();
	VOID Registe(HITimerMgrReceiver *receiver, INT id, DOUBLE intervalSecond, HTime const *time = NULL);
	VOID Unregiste(HITimerMgrReceiver *receiver, INT id);

	VOID Update();
};