#include "CoordinateAxisViewItem.h"

#include "program.h"
#include "Common/CommonCode.h"

extern HProgram *g_program;

//--------·Ö½çÏß-----------------------------------------------------------------
VOID HCoordinateAxisViewItem::Load() {
	m_device = g_program->Get_m_device();
	D3DXMatrixTranslation(&m_worldPos, 1.0f, 1.0f, 1.0f);
}

VOID HCoordinateAxisViewItem::Unload() {
}

VOID HCoordinateAxisViewItem::Show() {
	HRESULT hr;

	hr = m_device->CreateVertexBuffer(
		14 * sizeof(HXYZCVertex),
		D3DUSAGE_WRITEONLY,
		HXYZCVertex::FVF,
		D3DPOOL_MANAGED,
		&m_vertexBuffer,
		0
	);
	HXYZCVertex *data;
	hr = m_vertexBuffer->Lock(0, 0, (VOID**)(&data), 0);
	{
		int i = 0;
		data[i++] = HXYZCVertex(0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0));
		data[i++] = HXYZCVertex(10.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0));
		data[i++] = HXYZCVertex(0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0));
		data[i++] = HXYZCVertex(0.0f, 10.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0));
		data[i++] = HXYZCVertex(0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255));
		data[i++] = HXYZCVertex(0.0f, 0.0f, 10.0f, D3DCOLOR_XRGB(0, 0, 255));

		data[i++] = HXYZCVertex(20.0f, 0.0f, 20.0f, D3DCOLOR_XRGB(255, 0, 0));
		data[i++] = HXYZCVertex(-20.0f, 0.0f, 20.0f, D3DCOLOR_XRGB(255, 0, 0));
		data[i++] = HXYZCVertex(-20.0f, 0.0f, 20.0f, D3DCOLOR_XRGB(255, 0, 0));
		data[i++] = HXYZCVertex(-20.0f, 0.0f, -20.0f, D3DCOLOR_XRGB(255, 0, 0));
		data[i++] = HXYZCVertex(-20.0f, 0.0f, -20.0f, D3DCOLOR_XRGB(255, 0, 0));
		data[i++] = HXYZCVertex(20.0f, 0.0f, -20.0f, D3DCOLOR_XRGB(255, 0, 0));
		data[i++] = HXYZCVertex(20.0f, 0.0f, -20.0f, D3DCOLOR_XRGB(255, 0, 0));
		data[i++] = HXYZCVertex(20.0f, 0.0f, 20.0f, D3DCOLOR_XRGB(255, 0, 0));
	}
	hr = m_vertexBuffer->Unlock();

	m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_device->SetRenderState(D3DRS_LIGHTING, FALSE);
}

VOID HCoordinateAxisViewItem::Hide() {
	if (m_vertexBuffer != NULL) {
		m_vertexBuffer->Release();
		m_vertexBuffer = NULL;
	}
}

VOID HCoordinateAxisViewItem::Update() {
	D3DXMATRIX itemLocate;
	D3DXMatrixTranslation(&itemLocate, 0.0f, 0.0f, 0.0f);
	m_device->SetTransform(D3DTS_WORLD, &itemLocate);

	m_device->BeginScene();
	{
		m_device->SetStreamSource(0, m_vertexBuffer, 0, sizeof(HXYZCVertex));
		m_device->SetFVF(HXYZCVertex::FVF);
		m_device->DrawPrimitive(
			D3DPT_LINELIST,
			0, 7
		);
	}
	m_device->EndScene();
}
