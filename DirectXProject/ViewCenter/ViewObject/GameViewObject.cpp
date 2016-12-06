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
	D3DXMatrixLookAtLH(&m_criterionLocate, &D3DXVECTOR3(1.0f, 1.0f, -5.0f), &D3DXVECTOR3(1.0f, 1.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	D3DXMatrixRotationY(&m_oldFmtLocateY, 0.0f);
	D3DXMatrixRotationX(&m_oldFmtLocateX, 0.0f);
	m_factLocate = m_criterionLocate * m_oldFmtLocateY * m_oldFmtLocateX;

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
	m_device->SetTransform(D3DTS_VIEW, &m_factLocate);
	m_coordinateAxix->Update();
}

BOOL HGameViewObject::OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam) {
	switch (eventType) {
	case WndProcEventType_MOUSEMOVE:
	{
		POINT const *center = g_program->Get_m_center();
		POINT curCursorPos;
		GetCursorPos(&curCursorPos);
		LONG xOffset = curCursorPos.x - center->x;
		LONG yOffset = curCursorPos.y - center->y;
		//视角旋转操作
		FLOAT angle;
		D3DXMATRIX ry;
		angle = (float)(xOffset * m_cameraSpeed);
		D3DXMatrixRotationY(&ry, angle / 2);
		D3DXMATRIX rx;
		angle = (float)(yOffset * m_cameraSpeed);
		D3DXMatrixRotationX(&rx, (0 - angle) / 2);
		m_factLocate = m_criterionLocate * m_oldFmtLocateY * ry * m_oldFmtLocateX * rx;
		if (m_isCursorNeedReset == TRUE) {
			SetCursorPos(center->x, center->y);
			m_oldFmtLocateY = m_oldFmtLocateY * ry;
			m_oldFmtLocateX = m_oldFmtLocateX * rx;
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
