#pragma once

#include "../ViewObjectMgr.h"
#include "EventCenter/WndProcEventMgr.h"

//--------分界线-----------------------------------------------------------------
class HIGameViewItem {
public:
	virtual void Load();
	virtual void Unload();
	virtual void Show();
	virtual void Hide();
	virtual void Update();
};

//--------分界线-----------------------------------------------------------------
class HGameViewObject : public HIViewObject, public HIWndProcEventReceiver {
private:
	float g_speed = 0.1F;
	float g_X = 0.0F;
	float g_Y = 0.0F;
	bool g_mouseDown = false;
	POINT g_lPoint = {};
	float g_lX = 0.0F;
	float g_lY = 0.0F;
	D3DXVECTOR3 eye = D3DXVECTOR3(1.0f, 2.0f, -3.0f);
	D3DXVECTOR3 at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	IDirect3DVertexBuffer9 *buff;

	IDirect3DDevice9 *m_device;

	HIGameViewItem *m_coordinateAxix;

public:
	virtual void Load();
	virtual void Unload();
	virtual void Show();
	virtual void Hide();
	virtual void OnGetFocus();
	virtual void OnLostFocus();
	virtual void Update();

public:
	virtual BOOL OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam);
};