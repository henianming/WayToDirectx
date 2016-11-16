#include "WndProcEventMgr.h"

BOOL WndProcEventMgr::Create() {
	int i;

	for (i = 0; i < EventType_Max; i++) {
		m_etv.push_back(new M_RL());
	}

	return TRUE;
}

BOOL WndProcEventMgr::Release() {
	M_ETV::iterator it = m_etv.begin();
	while (it != m_etv.end()) {
		delete *it;

		it++;
	}
	m_etv.clear();

	return TRUE;
}

void WndProcEventMgr::Subscribe(WndProcEventReceiver *receiver, EventType eventType) {
	M_RL *rl = m_etv.at(eventType);
	M_RL::iterator it = rl->begin();
	while (it != rl->end()) {
		if ((int)(*it) == (int)receiver) {
			return;
		}

		it++;
	}


	m_etv.at(eventType)->push_back(receiver);
}

void WndProcEventMgr::Unsubscribe(WndProcEventReceiver *receiver, EventType eventType) {
	M_RL *rl = m_etv.at(eventType);
	M_RL::iterator it = rl->begin();
	while (it != rl->end()) {
		if ((int)(*it) == (int)receiver) {
			rl->erase(it);
			return;
		}

		it++;
	}
}

BOOL WndProcEventMgr::FireEvent(EventType eventType, WPARAM wParam, LPARAM lParam) {
	BOOL isDealed = FALSE;

	M_RL *rl = m_etv.at(eventType);
	M_RL::iterator it = rl->begin();
	while (it != rl->end()) {
		if ((*it)->OnMessage(eventType, wParam, lParam) == TRUE) {
			isDealed = TRUE;
		}
		it++;
	}

	return isDealed;
}