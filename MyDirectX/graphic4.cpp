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
		3 * sizeof(MyVertex4),
		D3DUSAGE_WRITEONLY,
		MyVertex4::FVF,
		D3DPOOL_MANAGED,
		&m_vertexBuffer,
		0
	);
	MyVertex4 *myVertex;
	m_vertexBuffer->Lock(0, 0, (void**)(&myVertex), 0);

	myVertex[0] = MyVertex4(-1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 0));
	myVertex[1] = MyVertex4(0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(125, 255, 0));
	myVertex[2] = MyVertex4(1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0));

	m_vertexBuffer->Unlock();

	m_device->CreateIndexBuffer(
		3 * sizeof(DWORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&m_indexBuffer,
		0
	);
	DWORD *index;
	m_indexBuffer->Lock(0, 0, (void**)(&index), 0);

	index[0] = 0;
	index[1] = 1;
	index[2] = 3;

	m_indexBuffer->Unlock();

	m_device->SetRenderState(D3DRS_LIGHTING, false);
	m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	D3DXVECTOR3 eye(0.0f, 0.0f, -1.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMATRIX v;
	D3DXMatrixLookAtLH(&v, &eye, &target, &up);

	m_device->SetTransform(D3DTS_VIEW, &v);
	
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f,
		(float)800 / (float)450,
		1.0f,
		1000.0f
	);

	m_device->SetTransform(D3DTS_PROJECTION, &proj);

	

	return TRUE;
}

BOOL Graphic4::Hide() {
	
	return TRUE;
}

BOOL Graphic4::Update(void *data) {
	D3DXMATRIX Rx, Ry;
	D3DXMatrixRotationX(&Rx, 0.0f);
	D3DXMatrixRotationY(&Ry, 0.0f);
	D3DXMATRIX p = Rx * Ry;
	m_device->SetTransform(D3DTS_WORLD, &p);

	m_device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
					0xFF000000, 1.0F, 0);

	m_device->BeginScene();
	{

		m_device->SetFVF(MyVertex4::FVF);
		m_device->SetStreamSource(0, m_vertexBuffer, 0, sizeof(MyVertex4));
		m_device->SetIndices(m_indexBuffer);

		m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 3, 0, 1);
	}
	m_device->EndScene();
	m_device->Present(0, 0, 0, 0);
	return TRUE;
}

BOOL Graphic4::OnMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
	return FALSE;
}
