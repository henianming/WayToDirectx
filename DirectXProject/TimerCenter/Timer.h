#ifndef TIMER_H
#define TIMER_H

#include <Windows.h>
#include <map>

struct TimerData {
public:
	double m_intervalTime;
	double m_lastActiveTime;

public:
	TimerData(double intervalTime, double lastActiveTime);
};

class ITimerMgrReceiver {
public:
	virtual void OnTimer(int id) = 0;
};

class TimerMgr {
private:
	typedef std::map<int, TimerData> M_ID_INTERVAL;
	typedef std::map<ITimerMgrReceiver*, M_ID_INTERVAL*> M_RECEIVER_ID;

private:
	M_RECEIVER_ID m_receiver_id;
	LARGE_INTEGER m_frequency;

public:
	TimerMgr();

	void Registe(ITimerMgrReceiver *receiver, int id, double intervalSecond);
	void Unregiste(ITimerMgrReceiver *receiver, int id);

	void Update();

private:
	double GetCurTimeStamp();
};

#endif //TIMER_H