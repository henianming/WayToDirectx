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
	/*
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
	*/


	HRESULT hr;

	hr = m_device->CreateVertexBuffer(
		6 * sizeof(XYZCVertex),
		D3DUSAGE_WRITEONLY,
		XYZCVertex::FVF,
		D3DPOOL_MANAGED,
		&buff,
		0
	);
	XYZCVertex *data;
	hr = buff->Lock(0, 0, (void**)(&data), 0);
	{
		data[0] = XYZCVertex(0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0));
		data[1] = XYZCVertex(10.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0));
		data[2] = XYZCVertex(0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0));
		data[3] = XYZCVertex(0.0f, 10.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0));
		data[4] = XYZCVertex(0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255));
		data[5] = XYZCVertex(0.0f, 0.0f, 10.0f, D3DCOLOR_XRGB(0, 0, 255));
	}
	hr = buff->Unlock();

	/*
	D3DXVECTOR3 m_eye = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 m_at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMATRIX v;
	D3DXMatrixLookAtLH(&v, &m_eye, &m_at, &m_up);
	m_device->SetTransform(D3DTS_VIEW, &v);
	*/

	RECT rect;
	GetWindowRect(g_program->Get_m_hWnd(), &rect);
	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;
	D3DXMATRIX pf;
	D3DXMatrixPerspectiveFovLH(
		&pf,
		D3DX_PI * 0.5f,
		(float)w / (float)h,
		1.0f,
		1000.0f
	);
	m_device->SetTransform(D3DTS_PROJECTION, &pf);

	m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_device->SetRenderState(D3DRS_LIGHTING, false);
}

void HGameViewObject::Hide() {
	m_coordinateAxix->Hide();
}

void HGameViewObject::OnGetFocus() {
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, WndProcEventType_KeyDown);
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, WndProcEventType_KeyUp);
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, WndProcEventType_LBUTTONDOWN);
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, WndProcEventType_MOUSEMOVE);
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, WndProcEventType_LBUTTONUP);
}

void HGameViewObject::OnLostFocus() {
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, WndProcEventType_LBUTTONUP);
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, WndProcEventType_MOUSEMOVE);
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, WndProcEventType_LBUTTONDOWN);
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, WndProcEventType_KeyUp);
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, WndProcEventType_KeyDown);
}

void HGameViewObject::Update() {
	HRESULT hr;

	D3DXMATRIX camera;
	D3DXMatrixLookAtLH(&camera, &eye, &at, &up);
	hr = m_device->SetTransform(D3DTS_VIEW, &camera);
	/*
	m_coordinateAxix->Update();
	*/

	D3DXMATRIX Rx, Ry;
	D3DXMatrixRotationX(&Rx, g_X);
	D3DXMatrixRotationY(&Ry, g_Y);
	D3DXMATRIX p = Rx * Ry;
	m_device->SetTransform(D3DTS_WORLD, &p);

	m_device->BeginScene();
	{
		m_device->SetStreamSource(0, buff, 0, sizeof(XYZCVertex));
		m_device->SetFVF(XYZCVertex::FVF);
		m_device->DrawPrimitive(
			D3DPT_LINELIST,
			0, 3
		);
	}
	m_device->EndScene();
}

BOOL HGameViewObject::OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam) {
	switch (eventType) {
	case WndProcEventType_LBUTTONDOWN:
	{
		g_mouseDown = true;
		GetCursorPos(&g_lPoint);
		g_lX = g_X;
		g_lY = g_Y;
		return 0;
	}break;
	case WndProcEventType_MOUSEMOVE:
	{
		if (g_mouseDown) {
			POINT tempPoint;
			GetCursorPos(&tempPoint);
			g_Y = g_lY - (tempPoint.x - g_lPoint.x) / 360.0F;
			g_X = g_lX - (tempPoint.y - g_lPoint.y) / 360.0F;
		}
	}break;
	case WndProcEventType_LBUTTONUP:
	{
		g_mouseDown = false;
	}break;
	}
	return FALSE;
}
