#include "GameViewObject.h"

#include "program.h"
#include "Common/CommonCode.h"
#include "CoordinateAxisViewItem.h"

extern HProgram *g_program;

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
	D3DXMatrixLookAtLH(&m_cameraLocateNormal, &D3DXVECTOR3(-5.0f, -1.0f, -1.0f), &D3DXVECTOR3(2.0f, -1.0f, -1.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	//D3DXMatrixRotationYawPitchRoll(&m_cameraOldY, 0.1f * D3DX_PI, 0.0f, 0.0f);
	//D3DXMatrixRotationYawPitchRoll(&m_cameraOldX, 0.0f, 0.1f * D3DX_PI, 0.0f);
	D3DXMatrixRotationYawPitchRoll(&m_cameraOldX, 0.1f * D3DX_PI, 0.1f * D3DX_PI, 0.0f);
	m_cameraLocateActual = m_cameraLocateNormal * m_cameraOldX;
	//m_cameraLocateActual = m_cameraLocateNormal * m_cameraOldY * m_cameraOldX;

	m_coordinateAxix->Show();
}

VOID HGameViewObject::Hide() {
	m_coordinateAxix->Hide();
}

VOID HGameViewObject::OnGetFocus() {
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, WndProcEventType_MOUSEMOVE);
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, WndProcEventType_KeyDown);
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, WndProcEventType_KeyUp);
}

VOID HGameViewObject::OnLostFocus() {
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, WndProcEventType_KeyUp);
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, WndProcEventType_KeyDown);
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, WndProcEventType_MOUSEMOVE);
}

VOID HGameViewObject::Update() {
	m_device->SetTransform(D3DTS_VIEW, &m_cameraLocateActual);
	m_coordinateAxix->Update();
}

BOOL HGameViewObject::OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam) {
	switch (eventType) {
	case WndProcEventType_MOUSEMOVE:
	{/*
		POINT const *center = g_program->Get_m_center();
		POINT curCursorPos;
		GetCursorPos(&curCursorPos);
		LONG xOffset = curCursorPos.x - center->x;
		LONG yOffset = curCursorPos.y - center->y;
		if (ABS(xOffset) <= m_cursorResetDistance && ABS(yOffset) <= m_cursorResetDistance) {
			D3DXMATRIX cameraChangeY;
			D3DXMatrixRotationY(&cameraChangeY, 0 - (FLOAT)xOffset * m_cameraSpeed);
			D3DXMATRIX cameraChangeX;
			D3DXMatrixRotationX(&cameraChangeX, (FLOAT)yOffset * m_cameraSpeed);
			m_cameraLocateActual = m_cameraLocateNormal * m_cameraOldY * cameraChangeY * m_cameraOldX * cameraChangeX;

			if (m_isCursorNeedReset == TRUE) {
				SetCursorPos(center->x, center->y);
				m_cameraOldY = m_cameraOldY * cameraChangeY;
				m_cameraOldX = m_cameraOldX * cameraChangeX;
				m_isCursorNeedReset = FALSE;
			}
		} else {
			SetCursorPos(center->x, center->y);
		}*/
		return TRUE;
	}break;
	}

	return FALSE;
}

BOOL HGameViewObject::OnMessage(HInputEventType eventType, DOUBLE durationTime, DOUBLE firstActiveTimeStamp, BOOL isContinue) {
	switch (eventType) {
	case HInputEventType_W:
	{
	}break;
	case HInputEventType_A:
	{
	}break;
	case HInputEventType_S:
	{
	}break;
	case HInputEventType_D:
	{
	}break;
	case HInputEventType_SPACE:
	{
	}break;
	case HInputEventType_SHIFT:
	{
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
