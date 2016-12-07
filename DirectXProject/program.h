#pragma once

#include <d3d9.h>
#include "EventCenter/WndProcEventMgr.h"
#include "TimeCenter/Time.h"
#include "TimerCenter/Timer.h"
#include "ViewCenter/ViewObjectMgr.h"

//--------·Ö½çÏß-----------------------------------------------------------------
class HProgram : public HIWndProcEventReceiver, public HITimerMgrReceiver {
private:
	//event system
	HWndProcEventMgr m_wndProcEventMgr;

	//program system
	WNDCLASS m_wndClass;
	HWND m_hWnd;
	D3DPRESENT_PARAMETERS m_d3dPresentParameters;
	IDirect3D9 *m_iDirect3D9;
	IDirect3DDevice9 *m_device;

	//time system
	HTimeMgr m_timeMgr;
	HTime m_time;

	//timer system
	HTimerMgr m_timerMgr;

	//view object system
	HViewObjectMgr m_viewObjectMgr;

	//self data
	INT m_count;
	DOUBLE m_fpsRefreshIntervalSec = 1.0;
	DOUBLE m_fps;
	RECT m_rect;
	LONG m_width;
	LONG m_height;
	POINT m_center;

public:
	BOOL Create(HINSTANCE hInstance, INT showType);
	BOOL Release();
	BOOL Update();

	HWndProcEventMgr* Get_m_wndProcEventMgr();
	HWND Get_m_hWnd();
	IDirect3DDevice9* Get_m_device();
	HTimeMgr* Get_m_timeMgr();
	HTime* Get_m_time();
	HTimerMgr* Get_m_timerMgr();
	RECT const* Get_m_rect();
	LONG Get_m_width();
	LONG Get_m_height();
	POINT const* Get_m_center();

private:
	VOID InitWndClass(HINSTANCE hInstance);
	BOOL CreateWnd(HINSTANCE hInstance, INT showType);
	BOOL ReleaseWnd();
	VOID InitDirectPresentParameters();
	BOOL CreateDirectX();
	BOOL ReleaseDirectX();
	VOID SubscribeEvent();
	VOID UnsubscribeEvent();
	VOID RegisteTime();
	VOID UnregisteTime();
	VOID RegisteTimer();
	VOID UnregisteTimer();
	
	VOID UpdataFps();
	VOID TitleView();

public:
	virtual BOOL OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam);
	virtual VOID OnTimer(INT id);
};