#include "Timer.h"

#include <Windows.h>
#include "program.h"

extern HProgram *g_program;

//--------分界线-----------------------------------------------------------------
HTimerData::HTimerData(HTime const *time, DOUBLE intervalTime, DOUBLE lastActiveTime)
	: m_time(time), m_intervalTime(intervalTime), m_lastActiveTime(lastActiveTime) {
}

//--------分界线-----------------------------------------------------------------
BOOL HTimerMgr::Create() {
	g_program->Get_m_timeMgr()->Registe(&m_time);

	return TRUE;
}

BOOL HTimerMgr::Release() {
	g_program->Get_m_timeMgr()->Unregiste(&m_time);

	return TRUE;
}

VOID HTimerMgr::Registe(HITimerMgrReceiver *receiver, INT id, DOUBLE intervalSecond, HTime const *time) {
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
		DOUBLE nowTimeStame = time->Get_m_curTimeStamp();
		mii->insert(std::pair<INT, HTimerData>(id, HTimerData(time, intervalSecond, nowTimeStame)));
	}
}

VOID HTimerMgr::Unregiste(HITimerMgrReceiver *receiver, INT id) {
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

VOID HTimerMgr::Update() {
	M_RECEIVER_ID::iterator riIt = m_receiver_id.begin();
	while (riIt != m_receiver_id.end()) {
		M_ID_INTERVAL *iiMapTemp = riIt->second;
		M_ID_INTERVAL::iterator iiIt = iiMapTemp->begin();
		while (iiIt != iiMapTemp->end()) {
			DOUBLE nowTimeStamp = iiIt->second.m_time->Get_m_curTimeStamp();
			DOUBLE temp = nowTimeStamp - iiIt->second.m_lastActiveTime;

			if (temp > iiIt->second.m_intervalTime) {
				riIt->first->OnTimer(iiIt->first);
				iiIt->second.m_lastActiveTime += iiIt->second.m_intervalTime;
			}

			iiIt++;
		}

		riIt++;
	}
}