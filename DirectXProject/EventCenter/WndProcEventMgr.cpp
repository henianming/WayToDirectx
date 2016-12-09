#include "WndProcEventMgr.h"

//--------·Ö½çÏß-----------------------------------------------------------------
BOOL HWndProcEventMgr::Create() {
	INT i;

	for (i = 0; i < HWndProcEventType_MAX; i++) {
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

VOID HWndProcEventMgr::Subscribe(HIWndProcEventReceiver *receiver, HWndProcEventType eventType) {
	M_RL *rl = m_etv.at(eventType);
	M_RL::iterator it = rl->begin();
	while (it != rl->end()) {
		if ((INT)(*it) == (INT)receiver) {
			return;
		}

		it++;
	}

	m_etv.at(eventType)->push_back(receiver);
}

VOID HWndProcEventMgr::Unsubscribe(HIWndProcEventReceiver *receiver, HWndProcEventType eventType) {
	M_RL *rl = m_etv.at(eventType);
	M_RL::reverse_iterator rit = rl->rbegin();
	while (rit != rl->rend()) {
		if ((INT)(*rit) == (INT)receiver) {
			rl->erase((++rit).base());
			return;
		}

		rit++;
	}
}

BOOL HWndProcEventMgr::FireEvent(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam) {
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