#pragma once

#include <d3d9.h>
#include "GameViewObject.h"

//--------·Ö½çÏß-----------------------------------------------------------------
class HCoordinateAxisViewItem : public HIGameViewItem {
private:
	FLOAT g_speed = 0.1F;
	FLOAT g_X = 0.0F;
	FLOAT g_Y = 0.0F;
	bool g_mouseDown = false;
	POINT g_lPoint = {};
	FLOAT g_lX = 0.0F;
	FLOAT g_lY = 0.0F;
	IDirect3DVertexBuffer9 *buff;

	D3DXMATRIX m_worldPos;

	IDirect3DDevice9 *m_device;
	IDirect3DVertexBuffer9 *m_vertexBuffer;

public:
	virtual VOID Load();
	virtual VOID Unload();
	virtual VOID Show();
	virtual VOID Hide();
	virtual VOID Update();
};