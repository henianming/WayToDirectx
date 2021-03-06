#pragma once

#include "i_graphic_object.h"
#include <d3dx9.h>

class MyVertex4 {
public:
	MyVertex4(FLOAT x, FLOAT y, FLOAT z, D3DCOLOR color);

	FLOAT m_x, m_y, m_z;
	D3DCOLOR m_color;
	static DWORD const FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
};

class Graphic4 : public IGraphicObject {
private:
	IDirect3DVertexBuffer9 *m_lineBuffer;

	IDirect3DVertexBuffer9 *m_vertexBuffer;
	IDirect3DIndexBuffer9 *m_indexBuffer;

	D3DXVECTOR3 m_eye;
	D3DXVECTOR3 m_at;
	D3DXVECTOR3 m_up;

public:
	Graphic4();
	virtual ~Graphic4();

	virtual BOOL Load(HWND hWnd, IDirect3DDevice9 *device);
	virtual BOOL Unload();
	virtual BOOL Show();
	virtual BOOL Hide();
	virtual BOOL Update(VOID *data);
	virtual BOOL OnMessage(UINT msg, WPARAM wParam, LPARAM lParam);
};