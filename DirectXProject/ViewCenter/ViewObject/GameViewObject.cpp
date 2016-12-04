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
	m_device = g_program->Get_m_device();

	m_coordinateAxix = new HCoordinateAxisViewItem();
	m_coordinateAxix->Load();
}

void HGameViewObject::Unload() {
	m_coordinateAxix->Unload();
	SAFEDELETENULL(m_coordinateAxix);
}

void HGameViewObject::Show() {
	HRESULT hr;

	RECT rect;
	GetWindowRect(g_program->Get_m_hWnd(), &rect);
	LONG w = rect.right - rect.left;
	LONG h = rect.bottom - rect.top;
	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovLH(
		&projection,
		0.5f * D3DX_PI,
		(float)w / (float)h,
		1.0f, 100.0f
	);
	hr = m_device->SetTransform(D3DTS_PROJECTION, &projection);

	m_coordinateAxix->Show();
}

void HGameViewObject::Hide() {
	m_coordinateAxix->Hide();
}

void HGameViewObject::OnGetFocus() {
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, WndProcEventType_KeyDown);
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, WndProcEventType_KeyUp);
}

void HGameViewObject::OnLostFocus() {
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, WndProcEventType_KeyUp);
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, WndProcEventType_KeyDown);
}

void HGameViewObject::Update() {
	HRESULT hr;

	D3DXMATRIX camera;
	D3DXVECTOR3 eye(1.0f, 2.0f, -3.0f);
	D3DXVECTOR3 at(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&camera, &eye, &at, &up);
	hr = m_device->SetTransform(D3DTS_VIEW, &camera);

	m_coordinateAxix->Update();
}

BOOL HGameViewObject::OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam) {
	return FALSE;
}
