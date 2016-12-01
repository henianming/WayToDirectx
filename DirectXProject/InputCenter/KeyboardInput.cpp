#include "KeyboardInput.h"

#include "program.h"

extern HProgram *g_program;

void HKeyboardInput::SubscribeEvent() {
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, WndProcEventType_KeyDown);
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, WndProcEventType_KeyUp);
}

void HKeyboardInput::UnsubscribeEnent() {
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, WndProcEventType_KeyDown);
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, WndProcEventType_KeyUp);
}

BOOL HKeyboardInput::IsKeyActive(WPARAM m_key) {
	M_KDL::iterator it = m_keyboardDataList.begin();
	while (it != m_keyboardDataList.end()) {
		if ((*it)->m_key == m_key) {
			return TRUE;
		}

		it++;
	}

	return FALSE;
}

BOOL HKeyboardInput::Create() {
	SubscribeEvent();

	return TRUE;
}

BOOL HKeyboardInput::Release() {
	UnsubscribeEnent();

	return TRUE;
}

BOOL HKeyboardInput::Update() {
	return TRUE;
}

BOOL HKeyboardInput::OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam) {
	switch (eventType) {
	case WndProcEventType_KeyDown:
	{
		BOOL isKeyActive = IsKeyActive(wParam);
		if (isKeyActive == TRUE) {
			return TRUE;
		}

		HKeyboard_Data *kd = new HKeyboard_Data();
		kd->m_key = wParam;
		kd->m_isContinue = TRUE;
		kd->m_lastActiveTimeStamp = g_program->Get_m_time()->Get_m_curTimeStamp();
		m_keyboardDataList.push_back(kd);

	}break;
	case WndProcEventType_KeyUp:
	{
	}break;
	}

	return FALSE;
}
