#pragma once

#include "../ViewObjectMgr.h"
#include "EventCenter/WndProcEventMgr.h"
#include "TimerCenter/Timer.h"

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
class HGameViewObject : public HIViewObject, public HIWndProcEventReceiver, public HITimerMgrReceiver {
private:
	IDirect3DDevice9 *m_device;

	HIGameViewItem *m_coordinateAxix;
	D3DXMATRIX m_oldCoordinateAxixLocate;
	D3DXMATRIX m_coordinateAxixLocate;
	BOOL m_isCursorNeedReset;

	double const m_cameraSpeed = (double)1 / (double)360 * D3DX_PI;

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
	virtual void OnTimer(int id);
};