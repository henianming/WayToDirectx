#pragma once

#include <d3d9.h>
#include "GameViewObject.h"

//--------·Ö½çÏß-----------------------------------------------------------------
class HCoordinateAxisViewItem : public HIGameViewItem {
private:
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