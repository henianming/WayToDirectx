#include "GameEventMgr.h"

BOOL HGameEventMgr::Create() {
	return TRUE;
}

BOOL HGameEventMgr::Release() {
	M_ETM::iterator mIt = m_etm.begin();
	while (mIt != m_etm.end()) {
		delete (mIt->first);
		delete (mIt->second);

		mIt++;
	}
	m_etm.clear();

	return TRUE;
}

VOID HGameEventMgr::Subscribe(HIGameEventReceiver *receiver, std::string const *eventType) {
	M_ETM::iterator mIt = m_etm.find(eventType);
	if (mIt == m_etm.end()) {
		m_etm.insert(M_ETP(new std::string(*eventType), new M_RL()));
		mIt = m_etm.find(eventType);
	}

	M_RL *tempRL = mIt->second;
	M_RL::iterator lIt = tempRL->begin();
	while (lIt != tempRL->end()) {
		if ((int)(*lIt) == (int)receiver) {
			return;
		}

		lIt++;
	}

	tempRL->push_back(receiver);
}

VOID HGameEventMgr::Unsubscribe(HIGameEventReceiver *receiver, std::string const *eventType) {
	M_ETM::iterator mIt = m_etm.find(eventType);
	if (mIt == m_etm.end()) {
		return;
	}

	M_RL *tempRL = mIt->second;
	M_RL::reverse_iterator lRit = tempRL->rbegin();
	while (lRit != tempRL->rend()) {
		if ((int)(*lRit) == (int)receiver) {
			tempRL->erase((++lRit).base());

			if (tempRL->size() == 0) {
				delete (mIt->first);
				delete (mIt->second);
				m_etm.erase(mIt);
			}

			return;
		}

		lRit++;
	}
}

BOOL HGameEventMgr::FireEvent(std::string const *eventType, VOID const *data) {
	BOOL isDealed = FALSE;

	M_ETM::iterator mIt = m_etm.find(eventType);
	if (mIt != m_etm.end()) {
		M_RL *tempRL = mIt->second;
		M_RL::iterator lIt = tempRL->begin();
		while (lIt != tempRL->end()) {
			if ((*lIt)->OnMessage(eventType, data)) {
				isDealed = TRUE;
			}
			lIt++;
		}
	}

	return isDealed;
}
