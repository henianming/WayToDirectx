#include "GameViewObject.h"

#include "program.h"
#include "Common/CommonCode.h"
#include "CoordinateAxisViewItem.h"
#include <string>

using namespace std;

extern HProgram *g_program;
extern string HGameEventStr_PROGRAM_SIZE;
extern string HGameEventStr_PROGRAM_MOVE;

//--------分界线-----------------------------------------------------------------
VOID HIGameViewItem::Load() {

}

VOID HIGameViewItem::Unload() {

}

VOID HIGameViewItem::Show() {

}

VOID HIGameViewItem::Hide() {

}

VOID HIGameViewItem::Update() {

}

//--------分界线-----------------------------------------------------------------
VOID HGameViewObject::CalculateCameraLocalActual() {
	D3DXMATRIX ry;
	D3DXMatrixRotationY(&ry, m_cameraRYChange);
	D3DXMATRIX rx;
	D3DXMatrixRotationX(&rx, m_cameraRXChange);
	m_cameraLocateActual = m_cameraLocateNormal * ry * rx;
}

VOID HGameViewObject::Load() {
	POINT const *center = g_program->Get_m_center();
	m_isCursorNeedReset = TRUE;
	m_device = g_program->Get_m_device();

	g_program->Get_m_timerMgr()->Registe(this, 1, 0.001);

	m_coordinateAxix = new HCoordinateAxisViewItem();
	m_coordinateAxix->Load();
}

VOID HGameViewObject::Unload() {
	m_coordinateAxix->Unload();
	SAFEDELETENULL(m_coordinateAxix);

	g_program->Get_m_timerMgr()->Unregiste(this, 1);
}

VOID HGameViewObject::Show() {
	INT w = g_program->Get_m_width();
	INT h = g_program->Get_m_height();
	D3DXMATRIX pf;
	D3DXMatrixPerspectiveFovLH(
		&pf,
		D3DX_PI * 0.33f,
		(FLOAT)w / (FLOAT)h,
		0.0f,
		1000.0f
	);
	m_device->SetTransform(D3DTS_PROJECTION, &pf);

	D3DXMatrixLookAtLH(&m_cameraLocateNormal, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_cameraRYNormal = 0.0f;
	m_cameraRXNormal = 0.0f;
	m_cameraRYChange = 0.0f;
	m_cameraRXChange = 0.0f;
	CalculateCameraLocalActual();

	m_coordinateAxix->Show();
}

VOID HGameViewObject::Hide() {
	m_coordinateAxix->Hide();
}

VOID HGameViewObject::OnGetFocus() {
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, HWndProcEventType_MOUSEMOVE);
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, HWndProcEventType_MOVE);

	g_program->Get_m_inputEventMgr()->Subscribe(this, HInputEventType_W);
	g_program->Get_m_inputEventMgr()->Subscribe(this, HInputEventType_A);
	g_program->Get_m_inputEventMgr()->Subscribe(this, HInputEventType_S);
	g_program->Get_m_inputEventMgr()->Subscribe(this, HInputEventType_D);
	g_program->Get_m_inputEventMgr()->Subscribe(this, HInputEventType_SPACE);
	g_program->Get_m_inputEventMgr()->Subscribe(this, HInputEventType_SHIFT);
}

VOID HGameViewObject::OnLostFocus() {
	g_program->Get_m_inputEventMgr()->Unsubscribe(this, HInputEventType_SHIFT);
	g_program->Get_m_inputEventMgr()->Unsubscribe(this, HInputEventType_SPACE);
	g_program->Get_m_inputEventMgr()->Unsubscribe(this, HInputEventType_D);
	g_program->Get_m_inputEventMgr()->Unsubscribe(this, HInputEventType_S);
	g_program->Get_m_inputEventMgr()->Unsubscribe(this, HInputEventType_A);
	g_program->Get_m_inputEventMgr()->Unsubscribe(this, HInputEventType_W);

	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, HWndProcEventType_MOVE);
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, HWndProcEventType_MOUSEMOVE);
}

VOID HGameViewObject::Update() {
	m_device->SetTransform(D3DTS_VIEW, &m_cameraLocateActual);
	m_coordinateAxix->Update();
}

BOOL HGameViewObject::OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam) {
	switch (eventType) {
	case HWndProcEventType_MOUSEMOVE:
	{
		POINT const *center = g_program->Get_m_center();
		POINT curCursorPos;
		GetCursorPos(&curCursorPos);
		LONG xOffset = curCursorPos.x - center->x;
		LONG yOffset = curCursorPos.y - center->y;
		if (ABS(xOffset) <= m_cursorResetDistance && ABS(yOffset) <= m_cursorResetDistance) {
			m_cameraRYChange = m_cameraRYNormal - (FLOAT)xOffset * m_cameraRSpeed;
			m_cameraRXChange = m_cameraRXNormal - (FLOAT)yOffset * m_cameraRSpeed;
			FLOAT Radian90 = 0.5f * D3DX_PI;
			if (m_cameraRXChange > Radian90) {
				m_cameraRXChange = Radian90;
			}
			if (m_cameraRXChange < (0 - Radian90)) {
				m_cameraRXChange = (0 - Radian90);
			}
			CalculateCameraLocalActual();

			if (m_isCursorNeedReset == TRUE) {
				SetCursorPos(center->x, center->y);
				m_cameraRYNormal = m_cameraRYChange;
				m_cameraRXNormal = m_cameraRXChange;
				m_isCursorNeedReset = FALSE;
			}
		} else {
			SetCursorPos(center->x, center->y);
		}
		return TRUE;
	}break;
	}

	return FALSE;
}

BOOL HGameViewObject::OnMessage(HInputEventType eventType, DOUBLE durationTime, DOUBLE firstActiveTimeStamp, BOOL isContinue) {
	switch (eventType) {
	case HInputEventType_A:
	{
		D3DXMATRIX posChange;
		D3DXMatrixTranslation(&posChange, (FLOAT)durationTime * m_cameraMSpeed, 0.0f, 0.0f);
		m_cameraLocateNormal = m_cameraLocateNormal * posChange;
		CalculateCameraLocalActual();
	}break;
	case HInputEventType_D:
	{
		D3DXMATRIX posChange;
		D3DXMatrixTranslation(&posChange, 0 - (FLOAT)durationTime * m_cameraMSpeed, 0.0f, 0.0f);
		m_cameraLocateNormal = m_cameraLocateNormal * posChange;
		CalculateCameraLocalActual();
	}break;
	case HInputEventType_SHIFT:
	{
		D3DXMATRIX posChange;
		D3DXMatrixTranslation(&posChange, 0.0f, (FLOAT)durationTime * m_cameraMSpeed, 0.0f);
		m_cameraLocateNormal = m_cameraLocateNormal * posChange;
		CalculateCameraLocalActual();
	}break;
	case HInputEventType_SPACE:
	{
		D3DXMATRIX posChange;
		D3DXMatrixTranslation(&posChange, 0.0f, 0 - (FLOAT)durationTime * m_cameraMSpeed, 0.0f);
		m_cameraLocateNormal = m_cameraLocateNormal * posChange;
		CalculateCameraLocalActual();
	}break;
	case HInputEventType_S:
	{
		D3DXMATRIX posChange;
		D3DXMatrixTranslation(&posChange, 0.0f, 0.0f, (FLOAT)durationTime * m_cameraMSpeed);
		m_cameraLocateNormal = m_cameraLocateNormal * posChange;
		CalculateCameraLocalActual();
	}break;
	case HInputEventType_W:
	{
		D3DXMATRIX posChange;
		D3DXMatrixTranslation(&posChange, 0.0f, 0.0f, 0 - (FLOAT)durationTime * m_cameraMSpeed);
		m_cameraLocateNormal = m_cameraLocateNormal * posChange;
		CalculateCameraLocalActual();
	}break;
	}
	return FALSE;
}

VOID HGameViewObject::OnTimer(INT id) {
	switch (id) {
	case 1:
	{
		m_isCursorNeedReset = TRUE;
	}break;
	}
}
