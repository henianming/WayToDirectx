#include "Timer.h"

#include <Windows.h>

TimerData::TimerData(double intervalTime, double lastActiveTime)
	: m_intervalTime(intervalTime), m_lastActiveTime(lastActiveTime) {
}

TimerMgr::TimerMgr() {
	QueryPerformanceFrequency(&m_frequency);
}

void TimerMgr::Registe(ITimerMgrReceiver *receiver, int id, double intervalSecond) {
	M_RECEIVER_ID::iterator riIt = m_receiver_id.find(receiver);
	if (riIt == m_receiver_id.end()) {
		m_receiver_id.insert(std::pair<ITimerMgrReceiver*, M_ID_INTERVAL*>(receiver, new M_ID_INTERVAL()));
	}

	M_ID_INTERVAL *mii = m_receiver_id.at(receiver);
	M_ID_INTERVAL::iterator iiIt = mii->find(id);
	if (iiIt == mii->end()) {
		double nowTimeStame = GetCurTimeStamp();
		mii->insert(std::pair<int, TimerData>(id, TimerData(intervalSecond, nowTimeStame)));
	}
}

void TimerMgr::Unregiste(ITimerMgrReceiver *receiver, int id) {
	M_RECEIVER_ID::iterator riIt = m_receiver_id.find(receiver);
	if (riIt == m_receiver_id.end()) {
		return;
	}

	M_ID_INTERVAL *mii = m_receiver_id.at(receiver);
	M_ID_INTERVAL::iterator iiIt = mii->find(id);
	if (iiIt == mii->end()) {
		return;
	}

	mii->erase(iiIt);
}

void TimerMgr::Update() {
	double nowTimeStamp = GetCurTimeStamp();

	M_RECEIVER_ID::iterator riIt = m_receiver_id.begin();
	while (riIt != m_receiver_id.end()) {
		M_ID_INTERVAL *iiMapTemp = riIt->second;
		M_ID_INTERVAL::iterator iiIt = iiMapTemp->begin();
		while (iiIt != iiMapTemp->end()) {
			double temp = nowTimeStamp - iiIt->second.m_lastActiveTime;

			if ((nowTimeStamp - iiIt->second.m_lastActiveTime) > iiIt->second.m_intervalTime) {
				riIt->first->OnTimer(iiIt->first);
				iiIt->second.m_lastActiveTime += iiIt->second.m_intervalTime;
			}

			iiIt++;
		}

		riIt++;
	}
}

double TimerMgr::GetCurTimeStamp() {
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return ((float)(count.QuadPart) / (float)(m_frequency.QuadPart));
}