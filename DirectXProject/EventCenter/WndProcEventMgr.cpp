#include "WndProcEventMgr.h"

BOOL HWndProcEventMgr::Create() {
	int i;

	for (i = 0; i < EventType_Max; i++) {
		m_etv.push_back(new M_RL());
	}

	return TRUE;
}

BOOL HWndProcEventMgr::Release() {
	M_ETV::iterator it = m_etv.begin();
	while (it != m_etv.end()) {
		delete *it;

		it++;
	}
	m_etv.clear();

	return TRUE;
}

void HWndProcEventMgr::Subscribe(HIWndProcEventReceiver *receiver, HEventType eventType) {
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

void HWndProcEventMgr::Unsubscribe(HIWndProcEventReceiver *receiver, HEventType eventType) {
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

BOOL HWndProcEventMgr::FireEvent(HEventType eventType, WPARAM wParam, LPARAM lParam) {
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