#include "CoordinateAxis.h"

#include "program.h"
extern Program *g_program;

void CoordinateAxis::Load() {
	HRESULT hr;
	IDirect3DDevice9* device = g_program->Get_m_device();

	hr = device->CreateVertexBuffer(
		6 * sizeof(XYZCVertex),
		D3DUSAGE_WRITEONLY,
		XYZCVertex::FVF,
		D3DPOOL_MANAGED,
		&m_vertexBuffer,
		0
	);
	if (FAILED(hr)) {
		return;
	}
	XYZCVertex *vertexTemp;
	m_vertexBuffer->Lock(0, 0, (void**)(&vertexTemp), 0);

	float const coordinateLen = 100.0f;
	vertexTemp[0] = XYZCVertex(0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0));
	vertexTemp[1] = XYZCVertex(coordinateLen, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0));
	vertexTemp[2] = XYZCVertex(0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertexTemp[3] = XYZCVertex(0.0f, coordinateLen, 0.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertexTemp[4] = XYZCVertex(0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255));
	vertexTemp[5] = XYZCVertex(0.0f, 0.0f, coordinateLen, D3DCOLOR_XRGB(0, 0, 255));

	m_vertexBuffer->Unlock();

	hr = device->CreateIndexBuffer(
		24 * sizeof(DWORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&m_indexBuffer,
		0
	);
	if (FAILED(hr)) {
		return;
	}
	DWORD *index;
	m_indexBuffer->Lock(0, 0, (void**)(&index), 0);



	m_indexBuffer->Unlock();
}

void CoordinateAxis::Unload() {

}

void CoordinateAxis::Show() {

}

void CoordinateAxis::Hide() {

}

void CoordinateAxis::Update() {

}