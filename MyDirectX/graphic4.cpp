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
	vertex[1] = MyVertex4(0.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(125, 0, 125));
	vertex[2] = MyVertex4(1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 125, 125));
	vertex[3] = MyVertex4(-1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0, 125, 125));
	vertex[4] = MyVertex4(0.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(125, 125, 255));
	vertex[5] = MyVertex4(0.0f, 0.0f, -1.0f, D3DCOLOR_XRGB(125, 125, 0));

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
		0,2,5,
		0,4,2,
		0,3,4,
		0,5,3,
		3,5,1,
		5,2,1,
		2,4,1,
		4,3,1
	};
	for (int i = 0; i < 24; i++) {
		index[i] = idx[i];
	}

	m_indexBuffer->Unlock();



	return TRUE;
}

BOOL Graphic4::Hide() {
	return TRUE;
}

BOOL Graphic4::Update(void *data) {
	return TRUE;
}

BOOL Graphic4::OnMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
	return FALSE;
}
