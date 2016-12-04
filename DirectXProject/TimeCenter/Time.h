#pragma once

#include <Windows.h>
#include <list>

class HTime {
private:
	double m_timeDensity;
	double m_curTimeStamp;

public:
	HTime();

	BOOL Set_m_timeDensity(double timeDensity);
	double Get_m_curTimeStamp() const;

	void AddTime(double realTime);
};

class HTimeMgr {
private:
	typedef std::list<HTime*> M_TL;

private:
	M_TL m_timeList;
	LARGE_INTEGER m_frequency;
	double m_curRealTimeStamp;

public:
	HTimeMgr();

	BOOL Create();
	BOOL Release();
	void Registe(HTime *time);
	void Unregiste(HTime *time);
	void Update();

	double GetCurRealTimeStamp();
};