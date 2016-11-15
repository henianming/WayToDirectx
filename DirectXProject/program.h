#ifndef PROGRAM_H
#define PROGRAM_H

#include <d3d9.h>
#include "EventCenter/WndProcEventMgr.h"

class Program {
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

private:
	void InitWndClass(HINSTANCE hInstance);
	BOOL CreateWnd(HINSTANCE hInstance, int showType);
	BOOL ReleaseWnd();
	void InitDirectPresentParameters();
	BOOL CreateDirectX();
	BOOL ReleaseDirectX();

public:
	Program();

	BOOL Create(HINSTANCE hInstance, int showType);
	BOOL Release();
	BOOL Update();

	WndProcEventMgr* GetWndProcEventMgr();

	double GetCurTimeStamp();
};

#endif //PROGRAM_H