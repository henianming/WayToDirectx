#ifndef I_GRAPHIC_OBJECT_H
#define I_GRAPHIC_OBJECT_H

#include <d3d9.h>

class IGraphicObject {
protected:
	HWND m_hWnd;
	IDirect3DDevice9 *m_device;

public:
	virtual ~IGraphicObject(){
	};

	virtual BOOL Load(HWND hWnd, IDirect3DDevice9 *device) = 0;
	virtual BOOL Unload() = 0;
	virtual BOOL Show() = 0;
	virtual BOOL Hide() = 0;
	virtual BOOL Update(void *data) = 0;
	virtual BOOL OnMessage(UINT msg, WPARAM wParam, LPARAM lParam) = 0;
};

#endif //I_GRAPHIC_OBJECT_H