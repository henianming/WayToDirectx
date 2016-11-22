#include "CoordinateAxis.h"

#include "program.h"
extern HProgram *g_program;

void HCoordinateAxis::Load() {
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
}

void HCoordinateAxis::Unload() {
	if (m_vertexBuffer) {
		m_vertexBuffer->Release();
		m_vertexBuffer = NULL;
	}
}

void HCoordinateAxis::Show() {

}

void HCoordinateAxis::Hide() {

}

void HCoordinateAxis::Update() {
	IDirect3DDevice9* device = g_program->Get_m_device();
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	device->BeginScene();
	{
		device->SetStreamSource(0, m_vertexBuffer, 0, sizeof(XYZCVertex));
		device->SetFVF(XYZCVertex::FVF);
		device->DrawPrimitive(D3DPT_LINELIST, 0, 3);
	}
	device->EndScene();
}