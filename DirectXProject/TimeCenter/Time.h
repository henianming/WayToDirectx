#pragma once

#include <Windows.h>
#include <list>

//--------�ֽ���-----------------------------------------------------------------
class HTime {
private:
	DOUBLE m_timeDensity;
	DOUBLE m_curTimeStamp;

public:
	HTime();

	BOOL Set_m_timeDensity(DOUBLE timeDensity);
	DOUBLE Get_m_curTimeStamp() const;

	VOID AddTime(DOUBLE realTime);
};

//--------�ֽ���-----------------------------------------------------------------
class HTimeMgr {
private:
	typedef std::list<HTime*> M_TL;

private:
	M_TL m_timeList;
	LARGE_INTEGER m_frequency;
	DOUBLE m_curRealTimeStamp;

public:
	HTimeMgr();

	BOOL Create();
	BOOL Release();
	VOID Registe(HTime *time);
	VOID Unregiste(HTime *time);
	VOID Update();

	DOUBLE GetCurRealTimeStamp();
};