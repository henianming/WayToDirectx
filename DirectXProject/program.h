#ifndef PROGRAM_H
#define PROGRAM_H

#include <d3d9.h>
#include "EventCenter/WndProcEventMgr.h"

class Program : public WndProcEventReceiver {
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

	//self data
	double m_oldTimeStamp;
	double m_fps;

private:
	void InitWndClass(HINSTANCE hInstance);
	BOOL CreateWnd(HINSTANCE hInstance, int showType);
	BOOL ReleaseWnd();
	void InitDirectPresentParameters();
	BOOL CreateDirectX();
	BOOL ReleaseDirectX();
	void SubscribeEvent();
	void UnsubscribeEvent();
	void UpdataFps();
	void TitleView();

public:
	virtual BOOL OnMessage(EventType eventType, WPARAM wParam, LPARAM lParam);

	Program();

	BOOL Create(HINSTANCE hInstance, int showType);
	BOOL Release();
	BOOL Update();

	WndProcEventMgr* GetWndProcEventMgr();

	double GetCurTimeStamp();
};

#endif //PROGRAM_H