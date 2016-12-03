#if 0
#include "InputEventMgr.h"

BOOL HInputEventMgr::Create() {
	int i;

	for (i = 0; i < HInputEventType_Max; i++) {
		m_etv.push_back(new M_RL());
	}

	return TRUE;
}

BOOL HInputEventMgr::Release() {
	M_ETV::iterator it = m_etv.begin();
	while (it != m_etv.end()) {
		delete *it;

		it++;
	}
	m_etv.clear();

	return TRUE;
}

void HInputEventMgr::Subscribe(HIInputEventReceiver *receiver, HInputEventType eventType) {
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

void HInputEventMgr::Unsubscribe(HIInputEventReceiver *receiver, HInputEventType eventType) {
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

BOOL HInputEventMgr::FireEvent(HInputEventType eventType, double durationTime, BOOL isContinue) {
	BOOL isDealed = FALSE;

	M_RL *rl = m_etv.at(eventType);
	M_RL::iterator it = rl->begin();
	while (it != rl->end()) {
		if ((*it)->OnMessage(eventType, durationTime, isContinue) == TRUE) {
			isDealed = TRUE;
		}
		it++;
	}

	return isDealed;
}
#endif