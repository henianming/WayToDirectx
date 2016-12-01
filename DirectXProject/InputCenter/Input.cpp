#include "Input.h"

#include "program.h"
#include "Common/CommonCode.h"
#include "KeyboardInput.h"

extern HProgram *g_program;

HInputMgr::HInputMgr() {
	m_keyboard = new HKeyboardInput();
}

HInputMgr::~HInputMgr() {
	SAFEDELETENULL(m_keyboard);
}

BOOL HInputMgr::Create() {
	SubscribeEvent();

	return TRUE;
}

BOOL HInputMgr::Release() {
	UnsubscribeEnent();

	return TRUE;
}

void HInputMgr::SubscribeEvent() {
	int i;
	for (i = HInputEventType_RK_Min; i < HInputEventType_RG_Max; i++) {
		g_program->Get_m_inputEventMgr()->Subscribe(this, (HInputEventType)i);
	}
}

void HInputMgr::UnsubscribeEnent() {
	int i;
	for (i = HInputEventType_RK_Min; i < HInputEventType_RG_Max; i++) {
		g_program->Get_m_inputEventMgr()->Unsubscribe(this, (HInputEventType)i);
	}
}

BOOL HInputMgr::OnMessage(HInputEventType eventType, double durationTime, BOOL isContinue) {
	return FALSE;
}