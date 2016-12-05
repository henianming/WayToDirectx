#pragma once

#include <d3d9.h>
#include "GameViewObject.h"

//--------·Ö½çÏß-----------------------------------------------------------------
class HCoordinateAxisViewItem : public HIGameViewItem {
private:
	float g_speed = 0.1F;
	float g_X = 0.0F;
	float g_Y = 0.0F;
	bool g_mouseDown = false;
	POINT g_lPoint = {};
	float g_lX = 0.0F;
	float g_lY = 0.0F;
	IDirect3DVertexBuffer9 *buff;

	D3DXMATRIX m_worldPos;

	IDirect3DDevice9 *m_device;
	IDirect3DVertexBuffer9 *m_vertexBuffer;

public:
	virtual void Load();
	virtual void Unload();
	virtual void Show();
	virtual void Hide();
	virtual void Update();
};