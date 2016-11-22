#ifndef TIMER_H
#define TIMER_H

#include <Windows.h>
#include <map>

struct HTimerData {
public:
	double m_intervalTime;
	double m_lastActiveTime;

public:
	HTimerData(double intervalTime, double lastActiveTime);
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
	LARGE_INTEGER m_frequency;

public:
	HTimerMgr();

	void Registe(HITimerMgrReceiver *receiver, int id, double intervalSecond);
	void Unregiste(HITimerMgrReceiver *receiver, int id);

	void Update();

private:
	double GetCurTimeStamp();
};

#endif //TIMER_H