#pragma once

#include <Windows.h>
#include <string>
#include <list>
#include <map>

//--------分界线-----------------------------------------------------------------
class HIGameEventReceiver {
public:
	virtual BOOL OnMessage(std::string const *eventType, VOID const *data) = 0;
};

//--------分界线-----------------------------------------------------------------
class HGameEventMgr {
private:
	struct HGameEventless {
		bool operator()(std::string const* _Left, std::string const* _Right) const {
			return ((*_Left) < (*_Right));
		}
	};
	typedef std::list<HIGameEventReceiver*> M_RL;
	typedef std::map<std::string const*, M_RL*, HGameEventless> M_ETM;
	typedef std::pair<std::string const*, M_RL*> M_ETP;

private:
	M_ETM m_etm;

public:
	BOOL Create();
	BOOL Release();

	VOID Subscribe(HIGameEventReceiver *receiver, std::string const *eventType);
	VOID Unsubscribe(HIGameEventReceiver *receiver, std::string const *eventType);
	BOOL FireEvent(std::string const *eventType, VOID const *data);
};