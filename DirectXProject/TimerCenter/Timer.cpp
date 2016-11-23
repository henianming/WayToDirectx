#include "Timer.h"

#include <Windows.h>
#include "program.h"

extern HProgram *g_program;

HTimerData::HTimerData(HTime const *time, double intervalTime, double lastActiveTime)
	: m_time(time), m_intervalTime(intervalTime), m_lastActiveTime(lastActiveTime) {
}

BOOL HTimerMgr::Create() {
	g_program->Get_m_timeMgr()->Registe(&m_time);

	return TRUE;
}

BOOL HTimerMgr::Release() {
	g_program->Get_m_timeMgr()->Unregiste(&m_time);

	return TRUE;
}

void HTimerMgr::Registe(HITimerMgrReceiver *receiver, int id, double intervalSecond, HTime const *time) {
	M_RECEIVER_ID::iterator riIt = m_receiver_id.find(receiver);
	if (riIt == m_receiver_id.end()) {
		m_receiver_id.insert(std::pair<HITimerMgrReceiver*, M_ID_INTERVAL*>(receiver, new M_ID_INTERVAL()));
	}

	M_ID_INTERVAL *mii = m_receiver_id.at(receiver);
	M_ID_INTERVAL::iterator iiIt = mii->find(id);
	if (iiIt == mii->end()) {
		if (time == NULL) {
			time = &m_time;
		}
		double nowTimeStame = time->Get_m_curTimeStamp();
		mii->insert(std::pair<int, HTimerData>(id, HTimerData(time, intervalSecond, nowTimeStame)));
	}
}

void HTimerMgr::Unregiste(HITimerMgrReceiver *receiver, int id) {
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

void HTimerMgr::Update() {
	M_RECEIVER_ID::iterator riIt = m_receiver_id.begin();
	while (riIt != m_receiver_id.end()) {
		M_ID_INTERVAL *iiMapTemp = riIt->second;
		M_ID_INTERVAL::iterator iiIt = iiMapTemp->begin();
		while (iiIt != iiMapTemp->end()) {
			double nowTimeStamp = iiIt->second.m_time->Get_m_curTimeStamp();
			double temp = nowTimeStamp - iiIt->second.m_lastActiveTime;

			if (temp > iiIt->second.m_intervalTime) {
				riIt->first->OnTimer(iiIt->first);
				iiIt->second.m_lastActiveTime += iiIt->second.m_intervalTime;
			}

			iiIt++;
		}

		riIt++;
	}
}