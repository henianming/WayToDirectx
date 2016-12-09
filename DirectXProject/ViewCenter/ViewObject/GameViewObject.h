#pragma once

#include "../ViewObjectMgr.h"
#include "EventCenter/WndProcEventMgr.h"
#include "EventCenter/InputEventMgr.h"
#include "EventCenter/GameEventMgr.h"
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
class HGameViewObject : public HIViewObject, public HIWndProcEventReceiver, public HIInputEventReceiver, public HITimerMgrReceiver {
private:
	IDirect3DDevice9 *m_device;

	HIGameViewItem *m_coordinateAxix;
	FLOAT m_cameraRYNormal;
	FLOAT m_cameraRXNormal;
	FLOAT m_cameraRYChange;
	FLOAT m_cameraRXChange;
	D3DXMATRIX m_cameraLocateNormal;
	D3DXMATRIX m_cameraLocateActual;
	BOOL m_isCursorNeedReset;

	LONG const m_cursorResetDistance = 100;
	FLOAT const m_cameraMSpeed = 1.0f;
	FLOAT const m_cameraRSpeed = (FLOAT)1 / (FLOAT)360 * D3DX_PI;

private:
	VOID CalculateCameraLocalActual();

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
	virtual BOOL OnMessage(HInputEventType eventType, DOUBLE durationTime, DOUBLE firstActiveTimeStamp, BOOL isContinue);
	virtual VOID OnTimer(INT id);
};