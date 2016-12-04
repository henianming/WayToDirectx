#include "CoordinateAxisViewItem.h"

#include "program.h"
#include "Common/CommonCode.h"

extern HProgram *g_program;

//--------·Ö½çÏß-----------------------------------------------------------------
void HCoordinateAxisViewItem::Load() {
	m_device = g_program->Get_m_device();
	D3DXMatrixTranslation(&m_worldPos, 0.0f, 0.0f, 0.0f);
}

void HCoordinateAxisViewItem::Unload() {
}

void HCoordinateAxisViewItem::Show() {
	HRESULT hr;

	hr = m_device->CreateVertexBuffer(
		6 * sizeof(XYZCVertex),
		D3DUSAGE_WRITEONLY,
		XYZCVertex::FVF,
		D3DPOOL_MANAGED,
		&m_vertexBuffer,
		0
	);
	XYZCVertex *data;
	hr = m_vertexBuffer->Lock(0, 0, (void**)(&data), 0);
	{
		data[0] = XYZCVertex(0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0));
		data[1] = XYZCVertex(10.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0));
		data[2] = XYZCVertex(0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0));
		data[3] = XYZCVertex(0.0f, 10.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0));
		data[4] = XYZCVertex(0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255));
		data[0] = XYZCVertex(0.0f, 0.0f, 10.0f, D3DCOLOR_XRGB(0, 0, 255));
	}
	hr = m_vertexBuffer->Unlock();
}

void HCoordinateAxisViewItem::Hide() {
	if (m_vertexBuffer != NULL) {
		m_vertexBuffer->Release();
		m_vertexBuffer = NULL;
	}
}

void HCoordinateAxisViewItem::Update() {
	HRESULT hr;

	hr = m_device->SetRenderState(D3DRS_LIGHTING, FALSE);
	hr = m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	hr = m_device->BeginScene();
	{
		//m_device->SetTransform(D3DTS_WORLD, &m_worldPos);
		D3DXMATRIX Rx, Ry;
		D3DXMatrixRotationX(&Rx, 0.0f);
		D3DXMatrixRotationY(&Ry, 0.0f);
		D3DXMATRIX p = Rx * Ry;
		m_device->SetTransform(D3DTS_WORLD, &p);

		m_device->SetStreamSource(1, m_vertexBuffer, 0, sizeof(XYZCVertex));
		m_device->SetFVF(XYZCVertex::FVF);
		m_device->DrawPrimitive(D3DPT_LINELIST, 0, 3);
	}
	hr = m_device->EndScene();
}