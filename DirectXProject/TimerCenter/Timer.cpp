#include "Timer.h"

void TimerMgr::Register(TimerMgrReceiver *receiver, int id, UINT intervalMilliSecond) {
	M_RECEIVER_ID::iterator riIt = m_receiver_id.find(receiver);
	if (riIt == m_receiver_id.end()) {
		m_receiver_id.insert(std::pair<TimerMgrReceiver*, M_ID_INTERVAL*>(receiver, new M_ID_INTERVAL()));
	}
}

void TimerMgr::Unregister(TimerMgrReceiver *receiver, int id) {

}
