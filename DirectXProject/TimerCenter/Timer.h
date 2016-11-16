#ifndef TIMER_H
#define TIMER_H

#include <minwindef.h>
#include <map>

class TimerMgrReceiver {
public:
	virtual void OnTimer(int id) = 0;
};

class TimerMgr {
private:
	typedef std::map<int, UINT> M_ID_INTERVAL;
	typedef std::map<TimerMgrReceiver*, M_ID_INTERVAL*> M_RECEIVER_ID;

private:
	M_RECEIVER_ID m_receiver_id;

public:
	void Register(TimerMgrReceiver *receiver, int id, UINT intervalMilliSecond);
	void Unregister(TimerMgrReceiver *receiver, int id);

	void Update();
};

#endif //TIMER_H