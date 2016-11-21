#ifndef PROGRAM_H
#define PROGRAM_H

#include <d3d9.h>
#include "EventCenter/WndProcEventMgr.h"
#include "TimerCenter/Timer.h"
#include "ViewCenter/ViewObjectMgr.h"

class Program : public IWndProcEventReceiver, public ITimerMgrReceiver {
private:
	//program system
	LARGE_INTEGER m_frequency;
	WNDCLASS m_wndClass;
	HWND m_hWnd;
	IDirect3D9 *m_iDirect3D9;
	D3DPRESENT_PARAMETERS m_d3dPresentParameters;
	IDirect3DDevice9 *m_device;

	//event system
	WndProcEventMgr m_wndProcEventMgr;

	//timer system
	TimerMgr m_timerMgr;

	//view object system
	ViewObjectMgr m_viewObjectMgr;

	//self data
	double m_oldTimeStamp;
	double m_fps;

public:
	Program();

	BOOL Create(HINSTANCE hInstance, int showType);
	BOOL Release();
	BOOL Update();

	HWND Get_m_hWnd();
	IDirect3DDevice9* Get_m_device();
	WndProcEventMgr* Get_m_wndProcEventMgr();

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
	virtual BOOL OnMessage(EventType eventType, WPARAM wParam, LPARAM lParam);
	virtual void OnTimer(int id);
};

#endif //PROGRAM_H