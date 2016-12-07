#pragma once

#include "../ViewObjectMgr.h"
#include "EventCenter/WndProcEventMgr.h"
#include "TimerCenter/Timer.h"

//--------分界线-----------------------------------------------------------------
class HIGameViewItem {
public:
	virtual VOID Load();
	virtual VOID Unload();
	virtual VOID Show();
	virtual VOID Hide();
	virtual VOID Update();
};

//--------分界线-----------------------------------------------------------------
class HGameViewObject : public HIViewObject, public HIWndProcEventReceiver, public HITimerMgrReceiver {
private:
	IDirect3DDevice9 *m_device;

	HIGameViewItem *m_coordinateAxix;
	D3DXMATRIX m_criterionLocate;
	D3DXMATRIX m_oldFmtLocateX;
	D3DXMATRIX m_oldFmtLocateY;
	D3DXMATRIX m_factLocate;
	BOOL m_isCursorNeedReset;

	LONG const m_cursorResetDistance = 100;
	DOUBLE const m_cameraSpeed = (DOUBLE)1 / (DOUBLE)360 * D3DX_PI;

public:
	virtual VOID Load();
	virtual VOID Unload();
	virtual VOID Show();
	virtual VOID Hide();
	virtual VOID OnGetFocus();
	virtual VOID OnLostFocus();
	virtual VOID Update();

public:
	virtual BOOL OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam);
	virtual VOID OnTimer(INT id);
};