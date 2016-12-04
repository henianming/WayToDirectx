#pragma once

#include "i_graphic_object.h"
#include <d3dx9.h>

class MyVertex3 {
public:
	MyVertex3(float x, float y, float z, D3DCOLOR color);

	float m_x, m_y, m_z;
	D3DCOLOR m_color;
	static DWORD const FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
};

class Graphic3 : public IGraphicObject {
private:
	IDirect3DVertexBuffer9 *m_vertexBuffer;
	IDirect3DIndexBuffer9 *m_indexBuffer;

	D3DXVECTOR3 m_cameraPos;
	D3DXVECTOR3 m_targetPos;
	D3DXVECTOR3 m_up;

	float g_speed = 0.1F;
	float g_X = 0.0F;
	float g_Y = 0.0F;
	bool g_mouseDown = false;
	POINT g_lPoint = {};
	float g_lX = 0.0F;
	float g_lY = 0.0F;

public:
	Graphic3();
	virtual ~Graphic3();

	virtual BOOL Load(HWND hWnd, IDirect3DDevice9 *device);
	virtual BOOL Unload();
	virtual BOOL Show();
	virtual BOOL Hide();
	virtual BOOL Update(void *data);
	virtual BOOL OnMessage(UINT msg, WPARAM wParam, LPARAM lParam);
};