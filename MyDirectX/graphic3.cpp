#include "graphic3.h"

MyVertex3::MyVertex3(FLOAT x, FLOAT y, FLOAT z, D3DCOLOR color)
	: m_x(x), m_y(y), m_z(z), m_color(color) {
}

Graphic3::Graphic3() {
}

Graphic3::~Graphic3() {
}

BOOL Graphic3::Load(HWND hWnd, IDirect3DDevice9 *device) {
	m_hWnd = hWnd;
	m_device = device;

	return TRUE;
}

BOOL Graphic3::Unload() {
	return TRUE;
}

BOOL Graphic3::Show() {
	HRESULT hResult;

	hResult = m_device->CreateVertexBuffer(
		3 * sizeof(MyVertex3),
		D3DUSAGE_WRITEONLY,
		MyVertex3::FVF,
		D3DPOOL_MANAGED,
		&m_vertexBuffer,
		0
		);
	if (FAILED(hResult)) {
		return FALSE;
	}

	MyVertex3 *myVertex;
	m_vertexBuffer->Lock(0, 0, (VOID**)(&myVertex), 0);

	myVertex[0] = MyVertex3(-1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(200, 0, 0));
	myVertex[1] = MyVertex3(0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(125, 255, 0));
	myVertex[2] = MyVertex3(1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0));

	m_vertexBuffer->Unlock();

	hResult = m_device->CreateIndexBuffer(
		3 * sizeof(DWORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&m_indexBuffer,
		0
		);
	if (FAILED(hResult)) {
		return FALSE;
	}

	DWORD *index;
	m_indexBuffer->Lock(0, 0, (VOID**)(&index), 0);

	index[0] = 0;
	index[1] = 1;
	index[2] = 3;

	m_indexBuffer->Unlock();

	m_cameraPos = D3DXVECTOR3(1.5f, 1.5f, -5.0f);
	m_targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMATRIX v;
	D3DXMatrixLookAtLH(&v, &m_cameraPos, &m_targetPos, &m_up);
	m_device->SetTransform(D3DTS_VIEW, &v);

	RECT rect;
	GetWindowRect(m_hWnd, &rect);
	LONG wndWidth = rect.right - rect.left;
	LONG wndHeight = rect.bottom - rect.top;
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5F,
		(FLOAT)wndWidth / (FLOAT)wndHeight,
		1.0F,
		1000.0F
		);
	m_device->SetTransform(D3DTS_PROJECTION, &proj);

	m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, true);
	m_device->SetRenderState(D3DRS_LIGHTING, false);

	return TRUE;
}

BOOL Graphic3::Hide() {
	if (m_indexBuffer) {
		m_indexBuffer->Release();
		m_indexBuffer = NULL;
	}

	if (m_vertexBuffer) {
		m_vertexBuffer->Release();
		m_vertexBuffer = NULL;
	}

	return TRUE;
}

BOOL Graphic3::Update(VOID *data) {
	if (!m_device) {
		return FALSE;
	}

	D3DXMATRIX Rx, Ry;
	D3DXMatrixRotationX(&Rx, g_X);
	D3DXMatrixRotationY(&Ry, g_Y);
	D3DXMATRIX p = Rx * Ry;
	m_device->SetTransform(D3DTS_WORLD, &p);

	m_device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			   0xFF000000, 1.0F, 0);

	m_device->BeginScene();
	{
		m_device->SetFVF(MyVertex3::FVF);
		m_device->SetStreamSource(0, m_vertexBuffer, 0, sizeof(MyVertex3));
		m_device->SetIndices(m_indexBuffer);
		m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 3, 0, 1);
	}
	m_device->EndScene();

	m_device->Present(0, 0, 0, 0);

	return TRUE;
}

BOOL Graphic3::OnMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_KEYUP:
	{
		switch (wParam) {
		case 'Z':
		{
			DWORD out;
			m_device->GetRenderState(D3DRS_FILLMODE, &out);
			out++;
			if (out == 4) {
				out = 1;
			}
			m_device->SetRenderState(D3DRS_FILLMODE, out);
		}break;
		case VK_ESCAPE:
		{
			DestroyWindow(m_hWnd);
			return TRUE;
		}break;
		}
	}break;
	case WM_LBUTTONDOWN:
	{
		g_mouseDown = true;
		GetCursorPos(&g_lPoint);
		g_lX = g_X;
		g_lY = g_Y;
		return 0;
	}break;
	case WM_MOUSEMOVE:
	{
		if (g_mouseDown) {
			POINT tempPoint;
			GetCursorPos(&tempPoint);
			g_Y = g_lY - (tempPoint.x - g_lPoint.x) / 360.0F;
			g_X = g_lX - (tempPoint.y - g_lPoint.y) / 360.0F;
		}
	}break;
	case WM_LBUTTONUP:
	{
		g_mouseDown = false;
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return TRUE;
	}break;
	}
	return FALSE;
}

