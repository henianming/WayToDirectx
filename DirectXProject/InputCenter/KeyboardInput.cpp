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

	return FALSE;
}
