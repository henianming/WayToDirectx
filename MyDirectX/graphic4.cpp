#include "graphic4.h"

#include <d3dx9.h>

MyVertex4::MyVertex4(float x, float y, float z, D3DCOLOR color)
	: m_x(x), m_y(y), m_z(z), m_color(color) {
}

Graphic4::Graphic4() {

}

Graphic4::~Graphic4() {

}

BOOL Graphic4::Load(HWND hWnd, IDirect3DDevice9 *device) {
	m_hWnd = hWnd;
	m_device = device;

	return TRUE;
}

BOOL Graphic4::Unload() {
	return TRUE;
}

BOOL Graphic4::Show() {
	m_device->CreateVertexBuffer(
		6 * sizeof(MyVertex4),
		D3DUSAGE_WRITEONLY,
		MyVertex4::FVF,
		D3DPOOL_MANAGED,
		&m_vertexBuffer,
		0
		);
	MyVertex4 *vertex;
	m_vertexBuffer->Lock(0, 0, (void**)(&vertex), 0);

	vertex[0] = MyVertex4(0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(125, 255, 125));
	vertex[1] = MyVertex4(1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 125, 125));
	vertex[2] = MyVertex4(0.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(125, 125, 255));
	vertex[3] = MyVertex4(-1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0, 125, 125));
	vertex[4] = MyVertex4(0.0f, 0.0f, -1.0f, D3DCOLOR_XRGB(125, 125, 0));
	vertex[5] = MyVertex4(0.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(125, 0, 125));

	m_vertexBuffer->Unlock();

	m_device->CreateIndexBuffer(
		24 * sizeof(DWORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&m_indexBuffer,
		0
		);
	DWORD *index;
	m_indexBuffer->Lock(0, 0, (void**)(&index), 0);

	DWORD idx[24] = {
		0,1,4,
		0,4,3,
		0,3,2,
		0,2,1,
		4,1,5,
		1,2,5,
		2,3,5,
		3,4,5
	};
	for (int i = 0; i < 24; i++) {
		index[i] = idx[i];
	}

	m_indexBuffer->Unlock();

	m_eye = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
	m_at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMATRIX v;
	D3DXMatrixLookAtLH(&v, &m_eye, &m_at, &m_up);
	m_device->SetTransform(D3DTS_VIEW, &v);

	RECT rect;
	GetWindowRect(m_hWnd, &rect);
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

	return TRUE;
}

BOOL Graphic4::Hide() {
	return TRUE;
}

BOOL Graphic4::Update(void *data) {
	m_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);


	m_device->BeginScene();
	{
		m_device->SetStreamSource(0, m_vertexBuffer, 0, sizeof(MyVertex4));
		m_device->SetFVF(MyVertex4::FVF);
		m_device->SetIndices(m_indexBuffer);
		m_device->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			0, 0, 6, 0, 8
		);
	}
	m_device->EndScene();

	m_device->Present(NULL, NULL, NULL, NULL);

	return TRUE;
}

BOOL Graphic4::OnMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_KEYDOWN:
	{
		switch (wParam) {
		case 'W':
		{
		}break;
		case 'S':
		{
		}break;
		case 'A':
		{
		}break;
		case 'D':
		{
		}break;
		case 'Q':
		{
		}break;
		case 'E':
		{
		}break;
		}
	}break;
	case WM_KEYUP:
	{
		switch (wParam) {
		case VK_ESCAPE:
		{
			DestroyWindow(m_hWnd);
		}break;
		}
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;
	}
	return FALSE;
}
