#include "Time.h"

//--------分界线-----------------------------------------------------------------
HTime::HTime()
	: m_timeDensity(1.0) {
}

BOOL HTime::Set_m_timeDensity(DOUBLE timeDensity) {
	m_timeDensity = timeDensity;
	return TRUE;
}

DOUBLE HTime::Get_m_curTimeStamp() const {
	return m_curTimeStamp;
}

VOID HTime::AddTime(DOUBLE realTime) {
	m_curTimeStamp += realTime * m_timeDensity;
}

//--------分界线-----------------------------------------------------------------
HTimeMgr::HTimeMgr() {
	QueryPerformanceFrequency(&m_frequency);
}

BOOL HTimeMgr::Create() {
	m_curRealTimeStamp = GetCurRealTimeStamp();

	return TRUE;
}

BOOL HTimeMgr::Release() {
	return TRUE;
}

VOID HTimeMgr::Registe(HTime *time) {
	M_TL::iterator it = m_timeList.begin();
	while (it != m_timeList.end()) {
		if ((INT*)time == (INT*)(*it)) {
			return;
		}

		it++;
	}

	m_timeList.push_back(time);
}

VOID HTimeMgr::Unregiste(HTime *time) {
	M_TL::iterator it = m_timeList.begin();
	while (it != m_timeList.end()) {
		if ((INT*)time == (INT*)(*it)) {
			m_timeList.erase(it);
			return;
		}

		it++;
	}
}

VOID HTimeMgr::Update() {
	DOUBLE oldRealTimeStamp = m_curRealTimeStamp;
	m_curRealTimeStamp = GetCurRealTimeStamp();
	DOUBLE realTime = m_curRealTimeStamp - oldRealTimeStamp;

	M_TL::iterator it = m_timeList.begin();
	while (it != m_timeList.end()) {
		(*it)->AddTime(realTime);

		it++;
	}
}

DOUBLE HTimeMgr::GetCurRealTimeStamp() {
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return ((DOUBLE)(count.QuadPart) / (DOUBLE)(m_frequency.QuadPart));
}
