#include "GameViewObject.h"

#include "program.h"
#include "Common/CommonCode.h"
#include "CoordinateAxisViewItem.h"

extern HProgram *g_program;

//--------分界线-----------------------------------------------------------------
void HIGameViewItem::Load() {

}

void HIGameViewItem::Unload() {

}

void HIGameViewItem::Show() {

}

void HIGameViewItem::Hide() {

}

void HIGameViewItem::Update() {

}

//--------分界线-----------------------------------------------------------------
void HGameViewObject::Load() {
	POINT const *center = g_program->Get_m_center();
	SetCursorPos(center->x, center->y);
	m_isCursorNeedReset = TRUE;
	m_device = g_program->Get_m_device();

	g_program->Get_m_timerMgr()->Registe(this, 1, 0.001);

	m_coordinateAxix = new HCoordinateAxisViewItem();
	m_coordinateAxix->Load();
}

void HGameViewObject::Unload() {
	m_coordinateAxix->Unload();
	SAFEDELETENULL(m_coordinateAxix);

	g_program->Get_m_timerMgr()->Unregiste(this, 1);
}

void HGameViewObject::Show() {
	D3DXMatrixLookAtLH(&m_coordinateAxixLocate, &D3DXVECTOR3(1.0f, 1.0f, -3.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	m_coordinateAxix->Show();
}

void HGameViewObject::Hide() {
	m_coordinateAxix->Hide();
}

void HGameViewObject::OnGetFocus() {
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, WndProcEventType_LBUTTONDOWN);
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, WndProcEventType_MOUSEMOVE);
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, WndProcEventType_LBUTTONUP);
}

void HGameViewObject::OnLostFocus() {
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, WndProcEventType_LBUTTONUP);
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, WndProcEventType_MOUSEMOVE);
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, WndProcEventType_LBUTTONDOWN);
}

void HGameViewObject::Update() {
	m_device->SetTransform(D3DTS_VIEW, &m_coordinateAxixLocate);
	m_coordinateAxix->Update();
}

BOOL HGameViewObject::OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam) {
	switch (eventType) {
	case WndProcEventType_MOUSEMOVE:
	{
		printf("move   %f\n", g_program->Get_m_time()->Get_m_curTimeStamp());
		POINT const *center = g_program->Get_m_center();
		POINT curCursorPos;
		GetCursorPos(&curCursorPos);
		LONG xOffset = curCursorPos.x - center->x;
		LONG yOffset = curCursorPos.y - center->y;
		//视角旋转操作
		D3DXMATRIX rx;
		D3DXMatrixRotationY(&rx, (float)(xOffset * m_cameraSpeed) / 10);
		D3DXMATRIX ry;
		D3DXMatrixRotationX(&ry, (float)(yOffset * m_cameraSpeed) / 10);
		m_coordinateAxixLocate = m_oldCoordinateAxixLocate * rx * ry;
		if (m_isCursorNeedReset == TRUE) {
			SetCursorPos(center->x, center->y);
			m_oldCoordinateAxixLocate = m_coordinateAxixLocate;
			m_isCursorNeedReset = FALSE;
		}
	}break;
	}

	return FALSE;
}

void HGameViewObject::OnTimer(int id) {
	switch (id) {
	case 1:
	{
		m_isCursorNeedReset = TRUE;
	}break;
	}
}
