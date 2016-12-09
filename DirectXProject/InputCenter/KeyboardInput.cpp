#include "KeyboardInput.h"

#include "program.h"

extern HProgram *g_program;

//--------·Ö½çÏß-----------------------------------------------------------------
VOID HKeyboardInput::CreateKeyboardMap() {
	m_keyEventMap.insert(M_KIEP('W', HInputEventType_W));
	m_keyEventMap.insert(M_KIEP('A', HInputEventType_A));
	m_keyEventMap.insert(M_KIEP('S', HInputEventType_S));
	m_keyEventMap.insert(M_KIEP('D', HInputEventType_D));
	m_keyEventMap.insert(M_KIEP(VK_SPACE, HInputEventType_SPACE));
	m_keyEventMap.insert(M_KIEP(VK_SHIFT, HInputEventType_SHIFT));
}

VOID HKeyboardInput::ReleaseKeyboardMap() {
	m_keyEventMap.clear();
}

VOID HKeyboardInput::SubscribeEvent() {
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, HWndProcEventType_KEYDOWN);
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, HWndProcEventType_KEYUP);
}

VOID HKeyboardInput::UnsubscribeEnent() {
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, HWndProcEventType_KEYUP);
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, HWndProcEventType_KEYDOWN);
}

HKeyboardInput::M_KDL::iterator HKeyboardInput::IsKeyActive(HInputEventType key) {
	M_KDL::iterator it = m_keyboardDataList.begin();
	while (it != m_keyboardDataList.end()) {
		if ((*it)->m_key == key) {
			return it;
		}

		it++;
	}

	return m_keyboardDataList.end();
}

HInputEventType HKeyboardInput::VKToRK(WPARAM key) {
	M_KIEM::iterator it = m_keyEventMap.find(key);
	if (it == m_keyEventMap.end()) {
		return HInputEventType_Min;
	} else {
		return it->second;
	}
}

BOOL HKeyboardInput::Create() {
	CreateKeyboardMap();

	SubscribeEvent();

	return TRUE;
}

BOOL HKeyboardInput::Release() {
	UnsubscribeEnent();

	ReleaseKeyboardMap();

	return TRUE;
}

BOOL HKeyboardInput::Update() {
	M_KDL::iterator it = m_keyboardDataList.begin();
	while (it != m_keyboardDataList.end()) {
		DOUBLE curTimeStamp = g_program->Get_m_time()->Get_m_curTimeStamp();
		DOUBLE keyDurationTime = curTimeStamp - (*it)->m_lastActiveTimeStamp;
		g_program->Get_m_inputEventMgr()->FireEvent((*it)->m_key, keyDurationTime, (*it)->m_firstActiveTimeStamp, TRUE);
		(*it)->m_lastActiveTimeStamp = curTimeStamp;

		it++;
	}

	return TRUE;
}

BOOL HKeyboardInput::OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam) {
	switch (eventType) {
	case HWndProcEventType_KEYDOWN:
	{
		HInputEventType keyTemp = VKToRK(wParam);
		if (keyTemp == HInputEventType_Min) {
			return FALSE;
		}

		M_KDL::iterator it = IsKeyActive(keyTemp);
		DOUBLE curTimeStamp = g_program->Get_m_time()->Get_m_curTimeStamp();
		if (it == m_keyboardDataList.end()) {
			HKeyboard_Data *kd = new HKeyboard_Data();
			kd->m_key = keyTemp;
			kd->m_firstActiveTimeStamp = curTimeStamp;
			kd->m_lastActiveTimeStamp = curTimeStamp;
			m_keyboardDataList.push_back(kd);
			it = IsKeyActive(keyTemp);
		} else {
			(*it)->m_lastActiveTimeStamp = curTimeStamp;
		}

		g_program->Get_m_inputEventMgr()->FireEvent(keyTemp, 0, (*it)->m_firstActiveTimeStamp, TRUE);
		return TRUE;
	}break;
	case HWndProcEventType_KEYUP:
	{
		HInputEventType keyTemp = VKToRK(wParam);
		if (keyTemp == HInputEventType_Min) {
			return FALSE;
		}

		M_KDL::iterator it = IsKeyActive(keyTemp);
		if (it != m_keyboardDataList.end()) {
			DOUBLE curTimeStamp = g_program->Get_m_time()->Get_m_curTimeStamp();
			DOUBLE keyDurationTime = curTimeStamp - (*it)->m_lastActiveTimeStamp;
			g_program->Get_m_inputEventMgr()->FireEvent(keyTemp, keyDurationTime, (*it)->m_firstActiveTimeStamp, FALSE);
			delete (*it);
			m_keyboardDataList.erase(it);
		}

		return TRUE;
	}break;
	}

	return FALSE;
}