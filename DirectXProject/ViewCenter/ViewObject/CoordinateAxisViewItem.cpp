#include "CoordinateAxisViewItem.h"

#include "program.h"
#include "Common/CommonCode.h"

extern HProgram *g_program;

//--------·Ö½çÏß-----------------------------------------------------------------
void HCoordinateAxisViewItem::Load() {
	m_device = g_program->Get_m_device();
	D3DXMatrixTranslation(&m_worldPos, 1.0f, 1.0f, 1.0f);
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
		data[5] = XYZCVertex(0.0f, 0.0f, 10.0f, D3DCOLOR_XRGB(0, 0, 255));
	}
	hr = m_vertexBuffer->Unlock();

	

	RECT rect;
	GetWindowRect(g_program->Get_m_hWnd(), &rect);
	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;
	D3DXMATRIX pf;
	D3DXMatrixPerspectiveFovLH(
		&pf,
		D3DX_PI * 0.33f,
		(float)w / (float)h,
		1.0f,
		1000.0f
	);
	m_device->SetTransform(D3DTS_PROJECTION, &pf);

	m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_device->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void HCoordinateAxisViewItem::Hide() {
	if (m_vertexBuffer != NULL) {
		m_vertexBuffer->Release();
		m_vertexBuffer = NULL;
	}
}

void HCoordinateAxisViewItem::Update() {
	D3DXMATRIX itemLocate;
	D3DXMatrixTranslation(&itemLocate, 0.0f, 0.0f, 0.0f);
	m_device->SetTransform(D3DTS_WORLD, &itemLocate);

	m_device->BeginScene();
	{
		m_device->SetStreamSource(0, m_vertexBuffer, 0, sizeof(XYZCVertex));
		m_device->SetFVF(XYZCVertex::FVF);
		m_device->DrawPrimitive(
			D3DPT_LINELIST,
			0, 3
		);
	}
	m_device->EndScene();
}
