#ifndef TIMER_H
#define TIMER_H

#include <Windows.h>
#include <map>

#include "TimeCenter/Time.h"

struct HTimerData {
public:
	HTime const *m_time;
	double m_intervalTime;
	double m_lastActiveTime;

public:
	HTimerData(HTime const *time, double intervalTime, double lastActiveTime);
};

class HITimerMgrReceiver {
public:
	virtual void OnTimer(int id) = 0;
};

class HTimerMgr {
private:
	typedef std::map<int, HTimerData> M_ID_INTERVAL;
	typedef std::map<HITimerMgrReceiver*, M_ID_INTERVAL*> M_RECEIVER_ID;

private:
	M_RECEIVER_ID m_receiver_id;
	HTime m_time;

public:
	BOOL Create();
	BOOL Release();
	void Registe(HITimerMgrReceiver *receiver, int id, double intervalSecond, HTime const *time = NULL);
	void Unregiste(HITimerMgrReceiver *receiver, int id);

	void Update();
};

#endif //TIMER_H