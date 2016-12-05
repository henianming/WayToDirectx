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

	m_device = g_program->Get_m_device();

	m_coordinateAxix = new HCoordinateAxisViewItem();
	m_coordinateAxix->Load();
}

void HGameViewObject::Unload() {
	m_coordinateAxix->Unload();
	SAFEDELETENULL(m_coordinateAxix);
}

void HGameViewObject::Show() {
	m_coordinateAxix->Show();
}

void HGameViewObject::Hide() {
	m_coordinateAxix->Hide();
}

void HGameViewObject::OnGetFocus() {
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, WndProcEventType_MOUSEMOVE);
}

void HGameViewObject::OnLostFocus() {
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, WndProcEventType_MOUSEMOVE);
}

void HGameViewObject::Update() {
	D3DXMATRIX camera;
	D3DXMatrixLookAtLH(&camera, &D3DXVECTOR3(1.0f, 1.0f, -3.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_device->SetTransform(D3DTS_VIEW, &camera);
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
		SetCursorPos(center->x, center->y);
	}break;
	}

	return FALSE;
}
