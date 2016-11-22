#ifndef PROGRAM_H
#define PROGRAM_H

#include <d3d9.h>
#include "EventCenter/WndProcEventMgr.h"
#include "TimeCenter/Time.h"
#include "TimerCenter/Timer.h"
#include "ViewCenter/ViewObjectMgr.h"

class HProgram : public HIWndProcEventReceiver, public HITimerMgrReceiver {
private:
	//program system
	WNDCLASS m_wndClass;
	HWND m_hWnd;
	IDirect3D9 *m_iDirect3D9;
	D3DPRESENT_PARAMETERS m_d3dPresentParameters;
	IDirect3DDevice9 *m_device;

	//time system
	HTime m_time;

	//event system
	HWndProcEventMgr m_wndProcEventMgr;

	//timer system
	HTimerMgr m_timerMgr;

	//view object system
	HViewObjectMgr m_viewObjectMgr;

	//self data
	double m_oldTimeStamp;
	double m_fps;

public:
	BOOL Create(HINSTANCE hInstance, int showType);
	BOOL Release();
	BOOL Update();

	HWND Get_m_hWnd();
	IDirect3DDevice9* Get_m_device();
	HWndProcEventMgr* Get_m_wndProcEventMgr();

	double GetCurTimeStamp();

private:
	void InitWndClass(HINSTANCE hInstance);
	BOOL CreateWnd(HINSTANCE hInstance, int showType);
	BOOL ReleaseWnd();
	void InitDirectPresentParameters();
	BOOL CreateDirectX();
	BOOL ReleaseDirectX();
	void SubscribeEvent();
	void UnsubscribeEvent();
	void RegisteTimer();
	void UnregisteTimer();
	void UpdataFps();
	void TitleView();

public:
	virtual BOOL OnMessage(HEventType eventType, WPARAM wParam, LPARAM lParam);
	virtual void OnTimer(int id);
};

#endif //PROGRAM_H