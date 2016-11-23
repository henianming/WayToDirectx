#include "Time.h"

HTime::HTime()
	: m_timeDensity(1.0) {

}

BOOL HTime::Set_m_timeDensity(double timeDensity) {
	m_timeDensity = timeDensity;
	return TRUE;
}

double HTime::Get_m_curTimeStamp() const {
	return m_curTimeStamp;
}

void HTime::AddTime(double realTime) {
	m_curTimeStamp += realTime * m_timeDensity;
}

HTimeMgr::HTimeMgr() {
	QueryPerformanceFrequency(&m_frequency);
}

void HTimeMgr::Registe(HTime *time) {
	M_TL::iterator it = m_timeList.begin();
	while (it != m_timeList.end()) {
		if ((int*)time == (int*)(*it)) {
			return;
		}

		it++;
	}

	m_timeList.push_back(time);
}

void HTimeMgr::Unregiste(HTime *time) {
	M_TL::iterator it = m_timeList.begin();
	while (it != m_timeList.end()) {
		if ((int*)time == (int*)(*it)) {
			m_timeList.erase(it);
			return;
		}

		it++;
	}
}

void HTimeMgr::Update() {
	double oldRealTimeStamp = m_curRealTimeStamp;
	m_curRealTimeStamp = GetCurRealTimeStamp();
	double realTime = m_curRealTimeStamp - oldRealTimeStamp;

	M_TL::iterator it = m_timeList.begin();
	while (it != m_timeList.end()) {
		(*it)->AddTime(realTime);

		it++;
	}
}

double HTimeMgr::GetCurRealTimeStamp() {
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return ((float)(count.QuadPart) / (float)(m_frequency.QuadPart));
}
