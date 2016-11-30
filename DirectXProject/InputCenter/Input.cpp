#include "Input.h"

#include "Common/CommonCode.h"
#include "KeyboardInput.h"

HInputMgr::HInputMgr() {
	m_keyboard = new HKeyboardInput();
}

HInputMgr::~HInputMgr() {
	SAFEDELETENULL(m_keyboard);
}

BOOL HInputMgr::Create() {
	return TRUE;
}

BOOL HInputMgr::Release() {
	return TRUE;
}

BOOL HInputMgr::OnMessage(HInputEventType eventType, double durationTime, BOOL isContinue) {
	return FALSE;
}